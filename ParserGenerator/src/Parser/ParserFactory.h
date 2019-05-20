#pragma once

#include "Parser.h"

namespace ParserGenerator {

	class ParserFactory
	{
	public:
		static bool Serialize(Parser* InParser, const std::string& FilePath);
		static bool Deserialize(Parser*& OutParser, const std::string& FilePath);
	};

}