#pragma once

#include <string>
#include "ListLexer.h"
#include "../../Lexer/Token.h"

class ListInterpreter
{
public:
	static void Analyse(const std::string& ListContent, std::vector<ParserCore::Node_CONST*>& OutNodes);

protected:
	static char GetTokenSymbol(ParserCore::Token* InToken);
};

