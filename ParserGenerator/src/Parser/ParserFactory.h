#pragma once

#include "Parser.h"
#include "../Builder/Alphabet.h"

namespace ParserGenerator {

	class ParserFactory
	{
	public:
		//static bool Serialize(Parser* InParser, const std::string& FilePath);
		//static bool Serialize(ParsingTable* InTable, Alphabet* InAlphabet, const std::string& FilePath);
		//static bool Deserialize(Parser*& OutParser, const std::string& FilePath);
		static bool Deserialize(ParsingTable*& OutTable, const std::string& InContent);
	};

}