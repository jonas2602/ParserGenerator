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
	bool Constant(Rule_constant*& OutRule);
	bool Divide(Rule_divide*& OutRule);
	bool Expression(Rule_expression*& OutRule);
	bool Multiplicative(Rule_multiplicative*& OutRule);
	bool Product(Rule_product*& OutRule);
	bool Subtract(Rule_subtract*& OutRule);
	bool Sum(Rule_sum*& OutRule);

protected:
	virtual const char* GetSerializedTable() const override;

};
