#pragma once
#include <string>
#include "Alphabet.h"
#include "../Parser/ParsingTable.h"
#include "../Parser/ParserConfig.h"
#include "../Lexer/LexerConfig.h"
#include "../Lexer/Automaton/Automaton.h"

namespace ParserGenerator {

	class ParserSerializer
	{
	public:
		// Human readable Versions
		static bool WriteAlphabet(Alphabet* InAlphabet, const std::string& FilePath);
		static bool WriteParsingTable(ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet, const std::string& FilePath);
		static bool WriteAutomaton(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet, const std::string& FilePath);

		// Versions stored in the Lexer/Parser class, used at runtime
		static bool SerializeParsingTable(ParsingTable* InTable, std::string& OutString);
		static bool SerializeAutomaton(Automaton::DFA* InDFA, std::string& OutString);

	protected:
		// Helper functions
		static void WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream);
		static void WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream);
	};

}