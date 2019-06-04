#include "ParserBuilder.h"

#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>

//#include "../Parser/ParseTable/ParsingTable.h"
#include "FirstFollowTable.h"
#include "ParserSerializer.h"
//#include "ParserSerializer.h"
//#include "../Generator/CodeGenerator.h"


namespace ParserGenerator {
	template<typename T>
	std::ostream& operator <<(std::ostream& os, const std::vector<T*>& v) {
		std::transform(v.begin(), v.end(),
			std::ostream_iterator<T>(os, " "),
			[](T const* ptr) -> T const& { return *ptr; }
		);
		return os;
	}

	ParserBuilder::ParserBuilder(const std::string& InSourceCode)
		: m_LexConfig(new LexerConfig()), m_ParsConfig(new ParserConfig())
	{
		if (!CreateConfigsFromSource(InSourceCode))
		{
			return;
		}

		if (!CreateAutomaton())
		{
			return;
		}

		if (!CreateParsingTable())
		{
			return;
		}

		bValidGrammar = true;
	}

	ParserBuilder::~ParserBuilder()
	{
		for (PC::Token* Token : m_TokenStream)
		{
			delete Token;
		}
		m_TokenStream.clear();

		delete m_ParseTreeRoot;

		delete m_LexConfig;
		delete m_ParsConfig;

		delete m_Alphabet;
		delete m_DFA;
		delete m_Table;
	}

	void ParserBuilder::Generate(const std::string& InRootPath, const std::string& InGrammarName, const std::string& InNamespaceName)
	{
		if (!bValidGrammar)
		{
			std::cout << "Can't generate Code from invalid Grammar" << std::endl;
			return;
		}

		// Create File Templates 
		ParserSerializer Serializer(InRootPath, InGrammarName, InNamespaceName, "", "doc");
		Serializer.WriteAlphabetDoc(m_Alphabet);
		Serializer.WriteAlphabetCode(m_Alphabet);
		Serializer.WriteParsingTableDoc(m_Table, m_ParsConfig, m_Alphabet);
		Serializer.WriteAutomatonDoc(m_DFA, m_LexConfig, m_Alphabet);
		Serializer.WriteRuleCode(m_ParsConfig, m_Alphabet);
		Serializer.WriteLexerCode(m_DFA, m_LexConfig, m_Alphabet);
		Serializer.WriteParserCode(m_Table, m_ParsConfig, m_Alphabet);
		Serializer.WriteVisitorCode(m_Alphabet);

		// Write to Disc
		Serializer.Finish();
	}

	bool ParserBuilder::CreateConfigsFromSource(const std::string& InSourceCode)
	{
		// Tokenize Source Code
		GrammarLexer Lexer = GrammarLexer(InSourceCode);
		if (!Lexer.Tokenize(m_TokenStream))
		{
			std::cout << "Failed to Tokenize Source Code" << std::endl;
			return false;
		}
		std::cout << m_TokenStream << std::endl << std::endl;

		// Try to parse Tokens as Tree
		GrammarParser Parser = GrammarParser(m_TokenStream);
		if (!Parser.Rulelist(m_ParseTreeRoot))
		{
			std::cout << "Failed to Parse Token Stream" << std::endl;
			return false;
		}

		// Extract Rule and Regex Elements from parsed Tree
		GrammarVisitor Visitor = GrammarVisitor(m_LexConfig, m_ParsConfig);
		if (!Visitor.Visit(m_ParseTreeRoot))
		{
			std::cout << "Failed to Analyse Parse Tree" << std::endl;
			return false;
		}

		// Check if grammar is valid
		if (m_LexConfig->GetDefinitionCount() < 1 || m_ParsConfig->GetProductionCount() < 1)
		{
			std::cout << "Grammer requires at least one Token and one Production!" << std::endl;
			return false;
		}

		// validate used Token and Rule Names
		bool AddEOS = false;
		for (const std::pair<std::string, RuleElement*>& Terminal : Visitor.GetTerminalMap())
		{
			// Ignore EOS because its predefined
			if (Terminal.first == PC::EOS_S)
			{
				AddEOS = true;
				continue;
			}

			if (!m_LexConfig->HasDefinition(Terminal.first))
			{
				std::cout << "No Terminal with name '" << Terminal.first << "' defined" << std::endl;
				return false;
			}
		}

		for (const std::pair<std::string, RuleElement*>& NonTerminal : Visitor.GetNonTerminalMap())
		{
			if (!m_ParsConfig->HasDefinition(NonTerminal.first))
			{
				std::cout << "No Rule with name '" << NonTerminal.first << "' defined" << std::endl;
				return false;
			}
		}

		// fill all references between tokens and productions
		if (!m_LexConfig->FillPlaceholder(Visitor.GetPlaceholder()))
		{
			return false;
		}
		m_LexConfig->CreateLiterals(Visitor.GetLiteralMap());

		// Create Alphabet from Token-/Ruletypes
		m_Alphabet = new Alphabet(m_LexConfig->CreateTokenIndexMap(), m_ParsConfig->CreateRuleIndexMap(), AddEOS);
		return true;
	}

	bool ParserBuilder::CreateAutomaton()
	{
		// Create Empty Automatons
		NFA TempNFA = NFA();
		m_DFA = new PCA::DFA();

		// Add all regex to "simple" NFA
		for (TokenDefinition* Token : m_LexConfig->GetRegexList())
		{
			int Priority = m_Alphabet->GetTokenIndex(Token->m_Name);
			std::cout << "Added " << Token->m_Name << " with Priority of " << Priority << std::endl;
			Token->m_Expression->Parse(&TempNFA, Token->m_Name, Priority);
		}

		// Create combined DFA
		TempNFA.CreateDFA(m_DFA);
		return true;
	}

	bool ParserBuilder::CreateParsingTable()
	{
		// Create Extended Prediction Table
		// if entries of [NonTerminal, Terminal] point to a rule of the NonTerminal again -> Left Recursion
		// if there are multiple possible entries for [NonTerminal, Terminal] -> Left Factoring
		// => Try to remove Left Factoring (Left recursion is not solvable with LL-Parsing)

		// Create Prediction Table
		FirstFollowTable FFTable(m_ParsConfig, m_Alphabet);
		m_Table = new PCT::ParsingTable();
		FFTable.CreateParsingTable(m_Table);

		return true;
	}

}