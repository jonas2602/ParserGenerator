// Automatically generated File
#include "GrammarParser.h"


GrammarParser::GrammarParser(const std::vector<PC::Token*>& TokenStream)
	: Parser(TokenStream)
{
	LoadParsingTable();
}

bool GrammarParser::Action(Rule_action*& OutRule)
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

bool GrammarParser::Lexerconst(Rule_lexerconst*& OutRule)
{
	OutRule = new Rule_lexerconst();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::CHARSET);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::DOT);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LEXERID);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::LITERAL);
			break;
		}
		case 4:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Regex, Rule_regex);
			TRY_MATCH(ETokenType::RP);
			break;
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GrammarParser::Lexeror(Rule_lexeror*& OutRule)
{
	OutRule = new Rule_lexeror();
	EnterRule(OutRule);
	
	CALL_CHILD(Operatorr, Rule_operatorr);
	CALL_CHILD(Lexeror2, Rule_lexeror2);
	
	ExitRule(OutRule);
	return true;
}

bool GrammarParser::Lexeror2(Rule_lexeror2*& OutRule)
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

bool GrammarParser::Lexerrule(Rule_lexerrule*& OutRule)
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

bool GrammarParser::Operatorr(Rule_operatorr*& OutRule)
{
	OutRule = new Rule_operatorr();
	EnterRule(OutRule);
	
	CALL_CHILD(Lexerconst, Rule_lexerconst);
	CALL_CHILD(Operatorr2, Rule_operatorr2);
	
	ExitRule(OutRule);
	return true;
}

bool GrammarParser::Operatorr2(Rule_operatorr2*& OutRule)
{
	OutRule = new Rule_operatorr2();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::PLUS);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::QUESTIONMARK);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::STAR);
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

bool GrammarParser::Parserconst(Rule_parserconst*& OutRule)
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
			TRY_MATCH(ETokenType::LITERAL);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Parseror, Rule_parseror);
			TRY_MATCH(ETokenType::RP);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::PARSERID);
			break;
		}
	}
	
	ExitRule(OutRule);
	return true;
}

bool GrammarParser::Parserlist(Rule_parserlist*& OutRule)
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

bool GrammarParser::Parseror(Rule_parseror*& OutRule)
{
	OutRule = new Rule_parseror();
	EnterRule(OutRule);
	
	CALL_CHILD(Parserlist, Rule_parserlist);
	CALL_CHILD(Parseror2, Rule_parseror2);
	
	ExitRule(OutRule);
	return true;
}

bool GrammarParser::Parseror2(Rule_parseror2*& OutRule)
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

bool GrammarParser::Parserrule(Rule_parserrule*& OutRule)
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

bool GrammarParser::Regex(Rule_regex*& OutRule)
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

bool GrammarParser::Rulelist(Rule_rulelist*& OutRule)
{
	OutRule = new Rule_rulelist();
	EnterRule(OutRule);
	
	switch (PredictProduction())
	{
		case 0:
		{
			TRY_MATCH(ETokenType::EOS);
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
			CALL_CHILD(Parserrule, Rule_parserrule);
			CALL_CHILD(Rulelist, Rule_rulelist);
			break;
		}
	}
	
	ExitRule(OutRule);
	return true;
}

const char* GrammarParser::GetSerializedTable() const
{
	return "0 4 0 0 12 1 1 3 2 1 6 0 1 9 1 1 10 3 1 16 4 2 3 0 2 6 0 2 9 0 2 10 0 2 16 0 3 3 1 3 4 1 3 6 1 3 9 1 3 10 1 3 12 1 3 14 0 3 15 1 3 16 1 4 3 0 5 3 0 5 6 0 5 9 0 5 10 0 5 16 0 6 3 3 6 4 3 6 5 1 6 6 3 6 7 2 6 8 0 6 9 3 6 10 3 6 12 3 6 14 3 6 15 3 6 16 3 7 3 0 7 10 1 7 11 3 7 16 2 8 3 0 8 10 0 8 11 0 8 12 1 8 14 1 8 15 1 8 16 0 9 3 0 9 10 0 9 11 0 9 12 0 9 14 0 9 15 0 9 16 0 10 12 1 10 14 0 10 15 1 11 11 0 12 3 0 12 4 1 12 6 0 12 9 0 12 10 0 12 12 1 12 15 1 12 16 0 13 -1 0 13 3 1 13 11 2 ";
}
