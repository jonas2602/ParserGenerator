// Automatically generated File
#pragma once

#include "GenAlphabet.h"
#include <Parser.h>

class GenLexer: public ParserGenerator::Lexer
{
public:
	GenLexer(const std::string& InSourceCode);

protected:
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};
