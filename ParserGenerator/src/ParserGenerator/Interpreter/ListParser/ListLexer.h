// Automatically generated File
#pragma once

#include "ListAlphabet.h"
#include <ParserCore.h>

class ListLexer: public PC::Lexer
{
public:
	ListLexer(const std::string& InSourceCode);

protected:
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;

};
