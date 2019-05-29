// Automatically generated File
#include "GenParser.h"


GenParser::GenParser(const std::vector<ParserGenerator::Token*>& TokenStream)
	: Parser(TokenStream)
{
	LoadParsingTable();
}

bool GenParser::Additive(Rule_additive*& OutRule)
{
	OutRule = new Rule_additive();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Multiplicative, Rule_multiplicative);
		}
		case 1:
		{
			CALL_CHILD(Subtract, Rule_subtract);
		}
		case 2:
		{
			CALL_CHILD(Sum, Rule_sum);
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Constant(Rule_constant*& OutRule)
{
	OutRule = new Rule_constant();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::FLOAT);
		}
		case 1:
		{
			TRY_MATCH(ETokenType::INTEGER);
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Additive, Rule_additive);
			TRY_MATCH(ETokenType::RP);
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Divide(Rule_divide*& OutRule)
{
	OutRule = new Rule_divide();
	EnterRule(OutRule);
	
	CALL_CHILD(Constant, Rule_constant);
	TRY_MATCH(ETokenType::SLASH);
	CALL_CHILD(Multiplicative, Rule_multiplicative);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Expression(Rule_expression*& OutRule)
{
	OutRule = new Rule_expression();
	EnterRule(OutRule);
	
	CALL_CHILD(Additive, Rule_additive);
	TRY_MATCH(ETokenType::EOS);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Multiplicative(Rule_multiplicative*& OutRule)
{
	OutRule = new Rule_multiplicative();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Constant, Rule_constant);
		}
		case 1:
		{
			CALL_CHILD(Divide, Rule_divide);
		}
		case 2:
		{
			CALL_CHILD(Product, Rule_product);
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Product(Rule_product*& OutRule)
{
	OutRule = new Rule_product();
	EnterRule(OutRule);
	
	CALL_CHILD(Constant, Rule_constant);
	TRY_MATCH(ETokenType::STAR);
	CALL_CHILD(Multiplicative, Rule_multiplicative);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Subtract(Rule_subtract*& OutRule)
{
	OutRule = new Rule_subtract();
	EnterRule(OutRule);
	
	CALL_CHILD(Multiplicative, Rule_multiplicative);
	TRY_MATCH(ETokenType::MINUS);
	CALL_CHILD(Additive, Rule_additive);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Sum(Rule_sum*& OutRule)
{
	OutRule = new Rule_sum();
	EnterRule(OutRule);
	
	CALL_CHILD(Multiplicative, Rule_multiplicative);
	TRY_MATCH(ETokenType::STAR);
	CALL_CHILD(Additive, Rule_additive);
	
	ExitRule(OutRule);
	return true;
}

const char* GenParser::GetSerializedTable() const
{
	return "0 1 0 0 2 0 0 4 0 1 1 1 1 2 0 1 4 2 2 1 0 2 2 0 2 4 0 3 1 0 3 2 0 3 4 0 4 1 0 4 2 0 4 4 0 5 1 0 5 2 0 5 4 0 6 1 0 6 2 0 6 4 0 7 1 0 7 2 0 7 4 0 ";
}
