#pragma once

#include <string>
#include "Automaton.h"
#include "..//..//Core.h"

namespace ParserGenerator::Automaton {
	
	class Factory
	{
	public:
		//static bool Serialize(Lexer* InLexer, const std::string& FilePath);
		//static bool Deserialize(Lexer*& OutLexer, const std::string& FilePath);
		static bool Deserialize(DFA*& OutAutomaton, const std::string& InContent);
	};

}