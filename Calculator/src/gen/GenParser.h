// Automatically generated File
#pragma once

#include "GenRules.h"
#include <Parser.h>

class GenParser: public ParserGenerator::Parser
{
public:
	GenParser(const std::vector<ParserGenerator::Token*>& TokenStream);

public:
	bool Additive(Rule_additive*& OutRule);
	bool Additive2(Rule_additive2*& OutRule);
	bool Constant(Rule_constant*& OutRule);
	bool Expression(Rule_expression*& OutRule);
	bool Multiplicative(Rule_multiplicative*& OutRule);
	bool Multiplicative2(Rule_multiplicative2*& OutRule);

protected:
	virtual const char* GetSerializedTable() const override;

};
