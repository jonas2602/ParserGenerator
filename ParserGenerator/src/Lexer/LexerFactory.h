#pragma once

#include <string>
#include "Lexer.h"
#include "../Parser/ParsingTable.h"
#include "Automaton/Automaton.h"

namespace ParserGenerator {
	
	class LexerFactory
	{
	public:
		//static bool Serialize(Lexer* InLexer, const std::string& FilePath);
		//static bool Deserialize(Lexer*& OutLexer, const std::string& FilePath);
		static bool Deserialize(Automaton::DFA*& OutAutomaton, const std::string& InContent);
	};

}