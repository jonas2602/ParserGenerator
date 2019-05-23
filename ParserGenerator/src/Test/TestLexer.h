#pragma once

#include "../Lexer/Lexer.h"




class TestLexer : public ParserGenerator::Lexer
{
public:
	TestLexer(const std::string& InSourceCode);
	~TestLexer();


	// Inherited via Lexer
	virtual std::string GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};

