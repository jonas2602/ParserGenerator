// Automatically generated File
#pragma once

#include "GenAlphabet.h"
#include <ParserCore.h>

class GenLexer: public PC::Lexer
{
public:
	GenLexer(const std::string& InSourceCode);

protected:
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};
