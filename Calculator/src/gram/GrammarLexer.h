// Automatically generated File
#pragma once

#include "GrammarAlphabet.h"
#include <ParserCore.h>

class GrammarLexer: public PC::Lexer
{
public:
	GrammarLexer(const std::string& InSourceCode);

protected:
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};
