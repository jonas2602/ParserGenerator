#include "TestParser.h"
#include <iostream>

#define TRY_MATCH(x) if(!Match(x)) return false; // std::cout << "Token mismatch, Expected: " << x << std::endl;
#define CALL_CHILD(func, type) { type* temp; if(!func(temp)) return false; }

TestParser::TestParser(const std::vector<ParserGenerator::Token*>& TokenStream)
	: Parser(TokenStream)
{
}


TestParser::~TestParser()
{
}

bool TestParser::Parserrule(Rule_parserrule*& OutRule)
{
	OutRule = new Rule_parserrule();
	EnterRule(OutRule);

	TRY_MATCH(ETokenType::PARSERID);
	TRY_MATCH(ETokenType::COLON);
	CALL_CHILD(Parseror, Rule_parseror);
	TRY_MATCH(ETokenType::SEMICOLON);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Parseror(Rule_parseror*& OutRule)
{
	OutRule = new Rule_parseror();
	EnterRule(OutRule);

	CALL_CHILD(Parserlist, Rule_parserlist);
	CALL_CHILD(Parseror2, Rule_parseror2);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Parseror2(Rule_parseror2*& OutRule)
{
	OutRule = new Rule_parseror2();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::PIPE);
			CALL_CHILD(Parseror2, Rule_parseror2);
			break;
		}
		case 1:
		{
			// EPSILON
			break;
		}
	}

	ExitRule(OutRule);
	return true;
}

bool TestParser::Parserlist(Rule_parserlist*& OutRule)
{
	OutRule = new Rule_parserlist();
	EnterRule(OutRule);

	CALL_CHILD(Parserconst, Rule_parserconst);
	CALL_CHILD(Parserlist2, Rule_parserlist2);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Parserlist2(Rule_parserlist2*& OutRule)
{
	OutRule = new Rule_parserlist2();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Parserconst, Rule_parserconst);
			CALL_CHILD(Parserlist2, Rule_parserlist2);
			break;
		}
		case 1:
		{
			// EPSILON
			break;
		}
	}

	ExitRule(OutRule);
	return true;
}

bool TestParser::Parserconst(Rule_parserconst*& OutRule)
{
	OutRule = new Rule_parserconst();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::LEXERID);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::PARSERID);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LITERAL);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::LEFTPARENTHESE);
			CALL_CHILD(Parseror, Rule_parseror);
			TRY_MATCH(ETokenType::RIGHTPARENTHESE);
			break;
		}
	}

	ExitRule(OutRule);
	return true;
}
