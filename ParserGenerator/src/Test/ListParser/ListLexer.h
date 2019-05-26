#pragma once

#include "../../Lexer/Lexer.h"

class ListLexer : public ParserGenerator::Lexer
{
public:
	ListLexer(const std::string& InSourceCode);
	~ListLexer();

protected:
	// Inherited via Lexer
	virtual std::string GetSerializedAutomaton() const override;
	virtual std::set<int> GetHiddenTokenTypes() const override;
};

