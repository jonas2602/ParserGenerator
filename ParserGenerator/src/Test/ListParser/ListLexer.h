#pragma once

#include "../../Lexer/Lexer.h"

class ListLexer : public ParserGenerator::Lexer
{
public:
	ListLexer(const std::string& InSourceCode);
	~ListLexer();

protected:
	// Inherited via Lexer
	virtual const char* GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;
};

