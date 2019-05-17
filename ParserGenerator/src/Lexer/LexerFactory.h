#pragma once

#include <string>
#include "Lexer.h"

namespace ParserGenerator {
	
	class LexerFactory
	{
	public:
		static bool Serialize(Lexer* InLexer, const std::string& FilePath);
		static bool Deserialize(Lexer*& OutLexer, const std::string& FilePath);
	};

}