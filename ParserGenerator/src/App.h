#pragma once

#include <string>
#include "Core.h"

namespace ParserGenerator {

	class PARSER_API App
	{
	public:
		static int main();

		static void Generate(const std::string& SourceCode);
		static void ListParser(const std::string& SourceCode);
	};
}