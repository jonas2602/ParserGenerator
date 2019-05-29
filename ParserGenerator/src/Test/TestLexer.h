#pragma once

#include "../Lexer/Lexer.h"




class TestLexer : public ParserGenerator::Lexer
{
public:
	TestLexer(const std::string& InSourceCode);
	~TestLexer();

protected:
	// Inherited via Lexer
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};

