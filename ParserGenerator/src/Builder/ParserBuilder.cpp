#include "ParserBuilder.h"

#include <iostream>
#include <filesystem>

#include "../Parser/ParseTable/ParsingTable.h"
#include "Alphabet.h"
#include "FirstFollowTable.h"
#include "ParserSerializer.h"
#include "../Generator/CodeGenerator.h"

namespace ParserGenerator {

	ParserBuilder::ParserBuilder(ParserConfig* InParsConfig, LexerConfig* InLexConfig)
		:m_LexConfig(InLexConfig), m_ParsConfig(InParsConfig)
	{
		// Create Alphabet first
		m_Alphabet = new Alphabet(m_LexConfig->GetTokenMap(), m_ParsConfig->GetNonTerminalMap());

		// Create Empty Automatons
		Automaton::NFA* TempNFA = new Automaton::NFA();
		m_DFA = new Automaton::DFA();

		// Add all regex to "simple" NFA
		for (const LexerConfigElement& Regex : m_LexConfig->GetRegexList())
		{
			int Priority = m_Alphabet->GetTokenIndex(Regex.m_Name);
			std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
			Regex.m_Expression->Parse(TempNFA, Regex.m_Name, Priority);
		}

		// Create combined DFA
		TempNFA->CreateDFA(m_DFA);

		// TODO: Create Surrounding Rule that captures EOS?

		// Process Config Data
		m_ParsConfig->FillTerminals();
		m_ParsConfig->Normalize();

		// Create Prediction Table
		FirstFollowTable FFTable(m_ParsConfig, m_Alphabet);
		m_Table = new ParseTable::ParsingTable();
		FFTable.CreateParsingTable(m_Table);

	}

	ParserBuilder::~ParserBuilder()
	{
		delete m_Alphabet;
		delete m_DFA;
		delete m_Table;
	}

	void ParserBuilder::Generate(const std::string& RootPath, const std::string& GrammarName)
	{
		//namespace fs = std::experimental::filesystem;

		//// Create Directory if it doesn't exist
		//fs::create_directories(fs::path(RootPath));

		//ParserSerializer::WriteAlphabet(m_Alphabet, (fs::path(RootPath) / fs::path(GrammarName + "Alphabet.alph")).string());
	
		ParserSerializer Serializer(RootPath, GrammarName, "", "doc");
		Serializer.WriteAlphabetDoc(m_Alphabet);
		Serializer.WriteAlphabetCode(m_Alphabet);
		Serializer.WriteParsingTableDoc(m_Table, m_ParsConfig, m_Alphabet);
		Serializer.WriteAutomatonDoc(m_DFA, m_LexConfig, m_Alphabet);
		Serializer.WriteRuleCode(m_ParsConfig, m_Alphabet);
		Serializer.WriteLexerCode(m_DFA, m_LexConfig, m_Alphabet);
		Serializer.Finish();

		

		//std::string AutomatonString;
		//ParserSerializer::SerializeAutomaton(m_DFA, AutomatonString);
		//std::string TableString;
		//ParserSerializer::SerializeParsingTable(m_Table, TableString);

		//std::cout << std::endl;
		//std::cout << AutomatonString << std::endl;
		//std::cout << TableString << std::endl;
	}
}