#pragma once

#include <string>
#include "ListParser/ListLexer.h"
#include <ParserCore.h>
#include "../Regex/RegExp.h"

namespace ParserGenerator {

	class ListInterpreter
	{
	public:
		static void Analyse(const std::string& ListContent, std::vector<Node_CONST*>& OutNodes);

	protected:
		static char GetTokenSymbol(ParserCore::Token* InToken);
	};

}