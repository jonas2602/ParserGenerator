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

std::string TestParser::GetSerializedTable() const
{
	return "0 0 0 0 12 1 1 13 0 2 1 3 2 3 2 2 4 1 2 5 4 2 6 0 3 1 0 3 3 0 3 4 0 3 5 0 3 6 0 4 0 1 4 1 1 " 
		"4 3 1 4 4 1 4 5 1 4 6 1 4 8 0 4 11 1 4 12 1 5 4 0 6 9 0 7 1 0 7 3 0 7 4 0 7 5 0 7 6 0 8 0 3 8 1 3 " 
		"8 3 3 8 4 3 8 5 3 8 6 3 8 8 3 8 9 1 8 10 2	8 11 3 8 12 3 8 13 0 9 10 0	10 4 0 10 5 2 10 6 3 10 7 1	" 
		"11 4 0	11 5 0 11 6 0 11 7 0 12 4 0 12 5 0 12 6 0 12 7 0 12 8 1 12 11 1 12 12 1 13 4 0 13 5 0 13 6 0 "
		"13 7 0	14 8 0 14 11 1 14 12 1 15 7 0 16 0 1 16 1 0 16 3 0 16 4 0 16 5 0 16 6 0 16 11 1 16 12 1 17 0 2 " 
		"17 4 1 17 7 0 ";
}
