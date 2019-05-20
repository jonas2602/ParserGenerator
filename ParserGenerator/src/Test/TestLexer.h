#pragma once

#include "../Lexer/Lexer.h";


enum TokenType {
	WS = 0,

};

class TestLexer : public ParserGenerator::Lexer
{
public:
	TestLexer();
	~TestLexer();
};

