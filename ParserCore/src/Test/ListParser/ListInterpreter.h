#pragma once

#include <string>
#include "ListLexer.h"
#include "../../Lexer/Token.h"

class ListInterpreter
{
public:
	static void Analyse(const std::string& ListContent, std::vector<ParserGenerator::Node_CONST*>& OutNodes);

protected:
	static char GetTokenSymbol(ParserGenerator::Token* InToken);
};

