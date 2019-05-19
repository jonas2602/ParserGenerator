#include <iostream>
#include <set>
#include "../Lexer/StateMachine.h"
#include "../Utils/Math.h"

#include "Parser.h"

namespace ParserGenerator {

	Parser::Parser(ParserConfig* InConfig)
		: m_Config(InConfig)
	{
		// Process Config Data
		m_Config->FillTerminals();
		m_Config->Normalize();

		// Create Prediction Table
		m_Table = new ParsingTable(m_Config);
	}

	Parser::~Parser()
	{
		delete m_Table;
	}

	ParseTree* Parser::BuildTree(std::vector<Token*> TokenStream)
	{
		// Push End Of Stream Token to the end of the TokenStream
		TokenStream.push_back(new Token("", ParserConfig::EOS, -1, -1, -1));

		const std::string & StartNonTerminal = m_Config->GetStartNonTerminal();
		Token * FirstToken = TokenStream[0];

		// Create Empty Parse Tree
		ParseTree * OutTree = new ParseTree();

		// Recursive Parse Tree construction
		std::vector<Token*>::iterator TokenIt = TokenStream.begin();
		WalkProduction(StartNonTerminal, TokenIt, OutTree, nullptr);

		// Has reached end of Stream?
		if ((*TokenIt)->GetTokenType() == ParserConfig::EOS)
		{
			std::cout << "Parser succeeded" << std::endl;
		}
		else
		{
			std::cout << "Parser finished before the end of the Token Stream was reached" << std::endl;
		}

		return OutTree;
	}

	bool Parser::WalkProduction(const std::string& NonTerminal, std::vector<Token*>::iterator& TokenStream, ParseTree* OutTree, ParseTree* ParentNode)
	{
		// Find Fitting Production
		ParserConfigElement* Production = m_Table->GetProduction(NonTerminal, (*TokenStream)->GetTokenType());
		ParseNode* ProductionNode = OutTree->InsertProductionNode(ParentNode, Production);

		// Iterate over all TokenClasses
		for (const std::string& TokenClass : Production->m_TokenClasses)
		{
			// Is Non Terminating?
			if (m_Config->IsNonTerminal(TokenClass))
			{
				// ... go one level deeper
				if (!WalkProduction(TokenClass, TokenStream, OutTree, ProductionNode))
				{
					// A Parser Error occured further down in the tree
					return false;
				}
			}
			else if (StateMachine::IsEpsilon(TokenClass))
			{
				// ... Nothing to do here 
			}
			else
			{
				// ... consume one token from the stream if the token class fits
				if (TokenClass == (*TokenStream)->GetTokenType())
				{
					std::cout << "Consume: \"" << (*TokenStream)->GetTokenData() << "\"" << std::endl;
					OutTree->InsertTokenNode(ParentNode, (*TokenStream));
					TokenStream++;
				}
				else
				{
					std::cout << "Error at [" << (*TokenStream)->GetLineNumber() << ", " << (*TokenStream)->GetColumnNumber() << "]" << std::endl;
					return false;
				}
			}
		}

		return true;
	}

}