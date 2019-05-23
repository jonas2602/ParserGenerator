#include "ParserBuilder.h"

#include <iostream>

#include "../Parser/ParsingTable.h"
#include "Alphabet.h"
#include "FirstFollowTable.h"
#include "ParserSerializer.h"

namespace ParserGenerator {

	ParserBuilder::ParserBuilder(ParserConfig* ParsConfig, LexerConfig* LexConfig)
	{
		// Create Alphabet first
		m_Alphabet = new Alphabet(LexConfig->GetTokenMap(), ParsConfig->GetNonTerminalMap());

		// Create Empty Automatons
		Automaton::NFA* TempNFA = new Automaton::NFA();
		m_DFA = new Automaton::DFA();

		// Add all regex to "simple" NFA
		for (const LexerConfigElement& Regex : LexConfig->GetRegexList())
		{
			int Priority = m_Alphabet->GetTokenIndex(Regex.m_Name);
			std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
			Regex.m_Expression->Parse(TempNFA, Regex.m_Name, Priority);
		}

		// Create combined DFA
		TempNFA->CreateDFA(m_DFA);

		// TODO: Create Surrounding Rule that captures EOS?

		// Process Config Data
		ParsConfig->FillTerminals();
		ParsConfig->Normalize();

		// Create Prediction Table
		FirstFollowTable FFTable(ParsConfig, m_Alphabet);
		m_Table = new ParsingTable();
		FFTable.CreateParsingTable(m_Table);

		ParserSerializer::WriteAlphabet(m_Alphabet, "res/AlphabetNew.alph");
		ParserSerializer::WriteParsingTable(m_Table, ParsConfig, m_Alphabet, "res/ParsingTableNew.tab");
		ParserSerializer::WriteAutomaton(m_DFA, LexConfig, m_Alphabet, "res/AutomatonNew.dfa");

		std::string AutomatonString;
		ParserSerializer::SerializeAutomaton(m_DFA, AutomatonString);
		std::string TableString;
		ParserSerializer::SerializeParsingTable(m_Table, TableString);

		std::cout << std::endl;
		//std::cout << AutomatonString << std::endl;
		std::cout << TableString << std::endl;
	}

	ParserBuilder::~ParserBuilder()
	{
		delete m_Alphabet;
		delete m_DFA;
		delete m_Table;
	}

}