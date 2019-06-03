#pragma once

#include <string>
#include "Core.h"

namespace ParserCore {

	class PARSER_API App
	{
	public:
		static int main();

		static void Generate(const std::string& SourceCode);
		static void ListParser();
	};
}