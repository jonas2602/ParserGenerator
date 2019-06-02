#include "ParserBuilder.h"

#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>

#include "../Interpreter/GrammarVisitor.h"
#include "../Interpreter/GrammarParser/GrammarLexer.h"
#include "../Interpreter/GrammarParser/GrammarParser.h"

//#include "../Parser/ParseTable/ParsingTable.h"
#include "FirstFollowTable.h"
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
	}

	ParserBuilder::ParserBuilder(ParserConfig* InParsConfig, LexerConfig* InLexConfig)
		:m_LexConfig(InLexConfig), m_ParsConfig(InParsConfig)
	{
		// Create Alphabet first
		//m_Alphabet = new Alphabet(m_LexConfig->GetTokenMap(), m_ParsConfig->GetNonTerminalMap());

		// Create Empty Automatons
		//Automaton::NFA* TempNFA = new Automaton::NFA();
		//m_DFA = new Automaton::DFA();

		// Add all regex to "simple" NFA
		//for (const TokenDefinition& Regex : m_LexConfig->GetRegexList())
		//{
		//	int Priority = m_Alphabet->GetTokenIndex(Regex.m_Name);
		//	std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
		//	Regex.m_Expression->Parse(TempNFA, Regex.m_Name, Priority);
		//}

		// Create combined DFA
		//TempNFA->CreateDFA(m_DFA);

		// TODO: Create Surrounding Rule that captures EOS?

		// Process Config Data
		//m_ParsConfig->FillTerminals();
		//m_ParsConfig->Normalize();

		// Create Prediction Table
		//FirstFollowTable FFTable(m_ParsConfig, m_Alphabet);
		//m_Table = new ParseTable::ParsingTable();
		//FFTable.CreateParsingTable(m_Table);

	}

	ParserBuilder::~ParserBuilder()
	{
		delete m_LexConfig;
		delete m_ParsConfig;

		delete m_Alphabet;
		/*delete m_DFA;
		delete m_Table;*/
	}

	void ParserBuilder::Generate(const std::string& InRootPath, const std::string& InGrammarName, const std::string& InNamespaceName)
	{
		//namespace fs = std::experimental::filesystem;

		//// Create Directory if it doesn't exist
		//fs::create_directories(fs::path(RootPath));

		//ParserSerializer::WriteAlphabet(m_Alphabet, (fs::path(RootPath) / fs::path(GrammarName + "Alphabet.alph")).string());



		//ParserSerializer Serializer(RootPath, GrammarName, "", "doc");
		//Serializer.WriteAlphabetDoc(m_Alphabet);
		//Serializer.WriteAlphabetCode(m_Alphabet);
		//Serializer.WriteParsingTableDoc(m_Table, m_ParsConfig, m_Alphabet);
		//Serializer.WriteAutomatonDoc(m_DFA, m_LexConfig, m_Alphabet);
		//Serializer.WriteRuleCode(m_ParsConfig, m_Alphabet);
		//Serializer.WriteLexerCode(m_DFA, m_LexConfig, m_Alphabet);
		//Serializer.WriteParserCode(m_Table, m_ParsConfig, m_Alphabet);
		//Serializer.WriteVisitorCode(m_ParsConfig);
		//Serializer.Finish();



		//std::string AutomatonString;
		//ParserSerializer::SerializeAutomaton(m_DFA, AutomatonString);
		//std::string TableString;
		//ParserSerializer::SerializeParsingTable(m_Table, TableString);

		//std::cout << std::endl;
		//std::cout << AutomatonString << std::endl;
		//std::cout << TableString << std::endl;
	}

	bool ParserBuilder::CreateConfigsFromSource(const std::string& InSourceCode)
	{
		// Tokenize Source Code
		GrammarLexer Lexer = GrammarLexer(InSourceCode);
		const std::vector<PC::Token*>& TokenStream = Lexer.GetTokenStream();
		std::cout << TokenStream << std::endl << std::endl;

		// Try to parse Tokens as Tree
		GrammarParser Parser = GrammarParser(TokenStream);
		Rule_rulelist* root;
		if (!Parser.Rulelist(root))
		{
			std::cout << "Failed to Parse Source Code" << std::endl;
			return false;
		}

		// Extract Rule and Regex Elements from parsed Tree
		GrammarVisitor Visitor = GrammarVisitor(m_LexConfig, m_ParsConfig);
		if (!Visitor.Visit(root))
		{
			std::cout << "Failed to Analyse Parse Tree" << std::endl;
			return false;
		}

		// validate used Token and Rule Names
		for (const std::pair<std::string, RuleElement*>& Terminal : Visitor.GetTerminalMap())
		{
			// Ignore EOS because its predefined
			if (Terminal.first == PC::EOS_S) continue;

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
		m_Alphabet = new Alphabet(m_LexConfig->CreateTokenIndexMap(), m_ParsConfig->CreateRuleIndexMap());
		return true;
	}

	bool  ParserBuilder::CreateAutomaton()
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