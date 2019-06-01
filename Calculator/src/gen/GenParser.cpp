// Automatically generated File
#include "GenParser.h"


GenParser::GenParser(const std::vector<PC::Token*>& TokenStream)
	: Parser(TokenStream)
{
	LoadParsingTable();
}

bool GenParser::Additive(Rule_additive*& OutRule)
{
	OutRule = new Rule_additive();
	EnterRule(OutRule);
	
	CALL_CHILD(Multiplicative, Rule_multiplicative);
	CALL_CHILD(Additive2, Rule_additive2);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Additive2(Rule_additive2*& OutRule)
{
	OutRule = new Rule_additive2();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::MINUS);
			CALL_CHILD(Multiplicative, Rule_multiplicative);
			CALL_CHILD(Additive2, Rule_additive2);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::PLUS);
			CALL_CHILD(Multiplicative, Rule_multiplicative);
			CALL_CHILD(Additive2, Rule_additive2);
			break;
		}
		case 2:
		{
			// EPSILON
			break;
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
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::INTEGER);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Additive, Rule_additive);
			TRY_MATCH(ETokenType::RP);
			break;
		}
	}
	
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
	
	CALL_CHILD(Constant, Rule_constant);
	CALL_CHILD(Multiplicative2, Rule_multiplicative2);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Multiplicative2(Rule_multiplicative2*& OutRule)
{
	OutRule = new Rule_multiplicative2();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::SLASH);
			CALL_CHILD(Constant, Rule_constant);
			CALL_CHILD(Multiplicative2, Rule_multiplicative2);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::STAR);
			CALL_CHILD(Constant, Rule_constant);
			CALL_CHILD(Multiplicative2, Rule_multiplicative2);
			break;
		}
		case 2:
		{
			// EPSILON
			break;
		}
	}
	
	ExitRule(OutRule);
	return true;
}

const char* GenParser::GetSerializedTable() const
{
	return "0 1 0 0 2 0 0 4 0 1 -1 2 1 3 2 1 6 0 1 7 1 2 1 1 2 2 0 2 4 2 3 1 0 3 2 0 3 4 0 4 1 0 4 2 0 4 4 0 5 -1 2 5 3 2 5 5 0 5 6 2 5 7 2 5 8 1 ";
}
