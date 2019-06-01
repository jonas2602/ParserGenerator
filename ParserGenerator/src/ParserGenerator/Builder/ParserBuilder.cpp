#include "ParserBuilder.h"

#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>

#include "../Interpreter/GrammarVisitor.h"
#include "../Interpreter/GrammarParser/GrammarLexer.h"
#include "../Interpreter/GrammarParser/GrammarParser.h"

//#include "../Parser/ParseTable/ParsingTable.h"
//#include "Alphabet.h"
//#include "FirstFollowTable.h"
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
	{
		GrammarLexer* Lexer = new GrammarLexer(InSourceCode);
		const std::vector<PC::Token*>& TokenStream = Lexer->GetTokenStream();
		std::cout << TokenStream << std::endl << std::endl;

		GrammarParser* Parser = new GrammarParser(TokenStream);
		Rule_rulelist* root;
		Parser->Rulelist(root);

		GrammarVisitor* Visitor = new GrammarVisitor();
		if (Visitor->Visit(root))
		{
			for (ParserConfigElement* Element : Visitor->GetParserConfig()->GetProductionList())
			{
				std::cout << Element << std::endl;
			}
		//	/*ParserBuilder builder(vis->GetParserConfig(), vis->GetLexerConfig());
		//	builder.Generate("src/gram/", "Grammar");*/
		}
		//else
		//{
		//	std::cout << "Failed to Analyse Parse Tree" << std::endl;
		//}
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
		//for (const LexerConfigElement& Regex : m_LexConfig->GetRegexList())
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
		/*delete m_Alphabet;
		delete m_DFA;
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
}