// Automatically generated File
#include "GenParser.h"


GenParser::GenParser(const std::vector<ParserGenerator::Token*>& TokenStream)
	: Parser(TokenStream)
{
	LoadParsingTable();
}

bool GenParser::Action(Rule_action*& OutRule)
{
	OutRule = new Rule_action();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::ARROW);
			TRY_MATCH(ETokenType::PARSERID);
		}
		case 1:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Lexerconst(Rule_lexerconst*& OutRule)
{
	OutRule = new Rule_lexerconst();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::CHARSET);
		}
		case 1:
		{
			TRY_MATCH(ETokenType::DOT);
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LEXERID);
		}
		case 3:
		{
			TRY_MATCH(ETokenType::LITERAL);
		}
		case 4:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Regex, Rule_regex);
			TRY_MATCH(ETokenType::RP);
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Lexeror(Rule_lexeror*& OutRule)
{
	OutRule = new Rule_lexeror();
	EnterRule(OutRule);
	
	CALL_CHILD(Operatorr, Rule_operatorr);
	CALL_CHILD(Lexeror2, Rule_lexeror2);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Lexeror2(Rule_lexeror2*& OutRule)
{
	OutRule = new Rule_lexeror2();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::PIPE);
			CALL_CHILD(Operatorr, Rule_operatorr);
			CALL_CHILD(Lexeror2, Rule_lexeror2);
		}
		case 1:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Lexerrule(Rule_lexerrule*& OutRule)
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

bool GenParser::Operatorr(Rule_operatorr*& OutRule)
{
	OutRule = new Rule_operatorr();
	EnterRule(OutRule);
	
	CALL_CHILD(Lexerconst, Rule_lexerconst);
	CALL_CHILD(Operatorr2, Rule_operatorr2);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Operatorr2(Rule_operatorr2*& OutRule)
{
	OutRule = new Rule_operatorr2();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::PLUS);
		}
		case 1:
		{
			TRY_MATCH(ETokenType::QUESTIONMARK);
		}
		case 2:
		{
			TRY_MATCH(ETokenType::STAR);
		}
		case 3:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Parserconst(Rule_parserconst*& OutRule)
{
	OutRule = new Rule_parserconst();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::LEXERID);
		}
		case 1:
		{
			TRY_MATCH(ETokenType::LITERAL);
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Parseror, Rule_parseror);
			TRY_MATCH(ETokenType::RP);
		}
		case 3:
		{
			TRY_MATCH(ETokenType::PARSERID);
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Parserlist(Rule_parserlist*& OutRule)
{
	OutRule = new Rule_parserlist();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Parserconst, Rule_parserconst);
			CALL_CHILD(Parserlist, Rule_parserlist);
		}
		case 1:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Parseror(Rule_parseror*& OutRule)
{
	OutRule = new Rule_parseror();
	EnterRule(OutRule);
	
	CALL_CHILD(Parserlist, Rule_parserlist);
	CALL_CHILD(Parseror2, Rule_parseror2);
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Parseror2(Rule_parseror2*& OutRule)
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
		}
		case 1:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Parserrule(Rule_parserrule*& OutRule)
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

bool GenParser::Regex(Rule_regex*& OutRule)
{
	OutRule = new Rule_regex();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Lexeror, Rule_lexeror);
			CALL_CHILD(Regex, Rule_regex);
		}
		case 1:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GenParser::Rulelist(Rule_rulelist*& OutRule)
{
	OutRule = new Rule_rulelist();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			CALL_CHILD(Lexerrule, Rule_lexerrule);
			CALL_CHILD(Rulelist, Rule_rulelist);
		}
		case 1:
		{
			CALL_CHILD(Parserrule, Rule_parserrule);
			CALL_CHILD(Rulelist, Rule_rulelist);
		}
		case 2:
		{
			// EPSILON
		}
	}
	
	ExitRule(OutRule);
	return true;
}

std::string GenParser::GetSerializedTable() const
{
	return "0 2 0 0 10 1 1 1 2 1 4 0 1 7 1 1 8 3 1 14 4 2 1 0 2 4 0 2 7 0 2 8 0 2 14 0 3 1 1 3 2 1 3 4 1 3 7 1 3 8 1 3 10 1 3 12 0 3 13 1 3 14 1 4 1 0 5 1 0 5 4 0 5 7 0 5 8 0 5 14 0 6 1 3 6 2 3 6 3 1 6 4 3 6 5 2 6 6 0 6 7 3 6 8 3 6 10 3 6 12 3 6 13 3 6 14 3 7 1 0 7 8 1 7 9 3 7 14 2 8 1 0 8 8 0 8 9 0 8 10 1 8 12 1 8 13 1 8 14 0 9 1 0 9 8 0 9 9 0 9 10 0 9 12 0 9 13 0 9 14 0 10 10 1 10 12 0 10 13 1 11 9 0 12 1 0 12 2 1 12 4 0 12 7 0 12 8 0 12 10 1 12 13 1 12 14 0 13 1 0 13 9 1 ";
}
