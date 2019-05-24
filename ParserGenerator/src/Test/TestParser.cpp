#include "TestParser.h"
#include <iostream>

#define TRY_MATCH(x) if(!Match(x)) return false; // std::cout << "Token mismatch, Expected: " << x << std::endl;
#define CALL_CHILD(func, type) { type* temp; if(!func(temp)) return false; }

TestParser::TestParser(const std::vector<ParserGenerator::Token*>& TokenStream)
	: Parser(TokenStream)
{
	LoadParsingTable();
}


TestParser::~TestParser()
{
}

bool TestParser::Rulelist(Rule_rulelist*& OutRule)
{
	OutRule = new Rule_rulelist();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Parserrule, Rule_parserrule);
			CALL_CHILD(Rulelist, Rule_rulelist);
			break;
		}
		case 1:
		{
			CALL_CHILD(Lexerrule, Rule_lexerrule);
			CALL_CHILD(Rulelist, Rule_rulelist);
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
			CALL_CHILD(Parserlist, Rule_parserlist);
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

	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Parserconst, Rule_parserconst);
			CALL_CHILD(Parserlist, Rule_parserlist);
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

//bool TestParser::Parserlist2(Rule_parserlist2*& OutRule)
//{
//	OutRule = new Rule_parserlist2();
//	EnterRule(OutRule);
//
//	switch (PredictProduction())
//	{
//		case 0:
//		{
//			CALL_CHILD(Parserconst, Rule_parserconst);
//			CALL_CHILD(Parserlist2, Rule_parserlist2);
//			break;
//		}
//		case 1:
//		{
//			// EPSILON
//			break;
//		}
//	}
//
//	ExitRule(OutRule);
//	return true;
//}

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

bool TestParser::Lexerrule(Rule_lexerrule*& OutRule)
{
	OutRule = new Rule_lexerrule();
	EnterRule(OutRule);

	TRY_MATCH(ETokenType::LEXERID);
	TRY_MATCH(ETokenType::COLON);
	CALL_CHILD(Regex, Rule_regex);
	CALL_CHILD(Action, Rule_action);
	TRY_MATCH(ETokenType::SEMICOLON);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Action(Rule_action*& OutRule)
{
	OutRule = new Rule_action();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::ARROW);
			TRY_MATCH(ETokenType::PARSERID);
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

bool TestParser::Regex(Rule_regex*& OutRule)
{
	OutRule = new Rule_regex();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Lexeror, Rule_lexeror);
			CALL_CHILD(Regex, Rule_regex);
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

bool TestParser::Lexeror(Rule_lexeror*& OutRule)
{
	OutRule = new Rule_lexeror();
	EnterRule(OutRule);

	CALL_CHILD(Operator, Rule_operator);
	CALL_CHILD(Lexeror2, Rule_lexeror2);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Lexeror2(Rule_lexeror2*& OutRule)
{
	OutRule = new Rule_lexeror2();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::PIPE);
			CALL_CHILD(Operator, Rule_operator);
			CALL_CHILD(Lexeror2, Rule_lexeror2);
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

bool TestParser::Operator(Rule_operator*& OutRule)
{
	OutRule = new Rule_operator();
	EnterRule(OutRule);

	CALL_CHILD(Lexerconst, Rule_lexerconst);
	CALL_CHILD(Operator2, Rule_operator2);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Operator2(Rule_operator2*& OutRule)
{
	OutRule = new Rule_operator2();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Anytime, Rule_anytime);
			break;
		}
		case 1:
		{
			CALL_CHILD(Once, Rule_once);
			break;
		}
		case 2:
		{
			CALL_CHILD(Optional, Rule_optional);
			break;
		}
		case 3:
		{
			// EPSILON
			break;
		}
	}

	ExitRule(OutRule);
	return true;
}

bool TestParser::Anytime(Rule_anytime*& OutRule)
{
	OutRule = new Rule_anytime();
	EnterRule(OutRule);

	TRY_MATCH(ETokenType::STAR);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Once(Rule_once*& OutRule)
{
	OutRule = new Rule_once();
	EnterRule(OutRule);

	TRY_MATCH(ETokenType::PLUS);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Optional(Rule_optional*& OutRule)
{
	OutRule = new Rule_optional();
	EnterRule(OutRule);

	TRY_MATCH(ETokenType::QUESTIONMARK);

	ExitRule(OutRule);
	return true;
}

bool TestParser::Lexerconst(Rule_lexerconst*& OutRule)
{
	OutRule = new Rule_lexerconst();
	EnterRule(OutRule);

	switch (PredictProduction())
	{
		case 0:
		{		
			TRY_MATCH(ETokenType::LEFTPARENTHESE);
			CALL_CHILD(Regex, Rule_regex);
			TRY_MATCH(ETokenType::RIGHTPARENTHESE);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::LEXERID);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::DOT);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::CHARSET);
			break;
		}
		case 4:
		{
			TRY_MATCH(ETokenType::LITERAL);
			break;
		}
	}

	ExitRule(OutRule);
	return true;
}

std::string TestParser::GetSerializedTable() const
{
	return "0 4 0 0 12 1 1 7 0 2 3 1 2 6 3 2 9 2 2 10 4 2 16 0 3 3 0 3 6 0 3 9 0 3 10 0 3 16 0 4 3 1 4 4 1 "
		"4 6 1 4 9 1 4 10 1 4 12 1 4 14 0 4 15 1 4 16 1 5 3 0 6 8 0 7 3 0 7 6 0 7 9 0 7 10 0 7 16 0 8 3 3 "
		"8 4 3 8 5 2 8 6 3 8 7 0 8 8 1 8 9 3 8 10 3 8 12 3 8 14 3 8 15 3 8 16 3 9 5 0 10 3 0 10 10 2 10 11 "
		"1 10 16 3 11 3 0 11 10 0 11 11 0 11 12 1 11 14 1 11 15 1 11 16 0 12 3 0 12 10 0 12 11 0 12 12 0 12 "
		"14 0 12 15 0 12 16 0 13 12 1 13 14 0 13 15 1 14 11 0 15 3 0 15 4 1 15 6 0 15 9 0 15 10 0 15 12 1 15 "
		"15 1 15 16 0 16 -1 2 16 3 1 16 11 0";
	/*return "0 4 0 0 12 1 1 7 0 2 3 1 2 6 3 2 9 2 2 10 4 2 16 0 3 3 0 3 6 0 3 9 0 3 10 0 3 16 0 4 3 1 4 4 1 "
		"4 6 1 4 9 1 4 10 1 4 12 1 4 14 0 4 15 1 4 16 1 5 3 0 6 8 0 7 3 0 7 6 0 7 9 0 7 10 0 7 16 0 8 3 "
		"3 8 4 3 8 5 2 8 6 3 8 7 0 8 8 1 8 9 3 8 10 3 8 12 3 8 14 3 8 15 3 8 16 3 9 5 0 10 3 0 10 10 2 10 "
		"11 1 10 16 3 11 3 0 11 10 0 11 11 0 11 12 1 11 14 1 11 15 1 11 16 0 12 3 0 12 10 0 12 11 0 12 12 "
		"0 12 14 0 12 15 0 12 16 0 13 12 1 13 14 0 13 15 1 14 11 0 15 3 0 15 4 1 15 6 0 15 9 0 15 10 0 15 "
		"12 1 15 15 1 15 16 0 16 3 1 16 11 0";*/
}
