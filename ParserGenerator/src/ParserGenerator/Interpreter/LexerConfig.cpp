#include "LexerConfig.h"

#include <utility>
#include <iostream>
#include "ParserConfig.h"

namespace ParserGenerator {

	LexerConfig::LexerConfig()
	{
	}


	LexerConfig::~LexerConfig()
	{
	}

	TokenDefinition* LexerConfig::AddToken(const std::string& Name, RegExp* Expression, ELexerAction Action)
	{
		// Token with given Name already exists?
		if (m_TokenMap.find(Name) != m_TokenMap.end())
		{
			std::cout << "Token with Name '" << Name << "' already defined" << std::endl;
			return nullptr;
		}

		// Create new Definition
		TokenDefinition* NewToken = new TokenDefinition(Name, Expression, Action);
		m_RegexList.insert(m_RegexList.begin(), NewToken);
		m_TokenMap[Name] = NewToken;

		return NewToken;
	}

	bool LexerConfig::FillPlaceholder(const std::vector<Node_PLACEHOLDER*>& InPlaceholder)
	{
		m_Placeholder = InPlaceholder;
		for (Node_PLACEHOLDER* Node : m_Placeholder)
		{
			if (m_TokenMap.find(Node->GetTerminalName()) == m_TokenMap.end())
			{
				std::cout << "Placeholder requires Token called '" << Node->GetTerminalName() << "' that has no corresponding Tokendefinition" << std::endl;
				return false;
			}

			TokenDefinition* ReferencedDefinition = m_TokenMap[Node->GetTerminalName()];
			Node->FillPlaceholder(ReferencedDefinition->m_Expression->GetRootNode());
		}

		return true;
	}

	void LexerConfig::CreateLiterals(const std::map<std::string, RuleElement*>& InLiteralMap)
	{
		std::map<std::string, TokenDefinition*> ExistingLiterals;

		// Search for all Tokendefinition that already represent Literals (only a sequence of characters)
		for (TokenDefinition* Definition : m_RegexList)
		{
			std::string OutLiteral;
			if (Definition->m_Expression->IsLiteral(OutLiteral))
			{
				ExistingLiterals[OutLiteral] = Definition;
			}
		}

		// Compare the given entries of the given Literal Map with the existing ones to avoid duplicates
		int LiteralCounter = 0;
		for (const std::pair<std::string, RuleElement*>& Pair : InLiteralMap)
		{
			TokenDefinition* LiteralDefinition = ExistingLiterals[Pair.first];
			if (!LiteralDefinition)
			{
				// ... create new definition
				std::string LiteralName = std::string("L__") + std::to_string(LiteralCounter++);
				LiteralDefinition = AddToken(LiteralName, new RegExp(RegExp::SEQUENCE(Pair.first)));
				ExistingLiterals[Pair.first] = LiteralDefinition;
			}

			Pair.second->m_Content = LiteralDefinition->m_Name;
		}
	}

	std::map<std::string, int> LexerConfig::CreateTokenIndexMap() const
	{
		std::map<std::string, int> TokenMap;

		for (int i = 0; i < m_RegexList.size(); i++)
		{
			TokenMap[m_RegexList[i]->m_Name] = i;
		}

		return TokenMap;
	}

}