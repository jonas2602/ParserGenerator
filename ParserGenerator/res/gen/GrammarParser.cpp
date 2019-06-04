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
			// EPSILON
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::ARROW);
			TRY_MATCH(ETokenType::PARSERID);
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
			TRY_MATCH(ETokenType::DOT);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Regex, Rule_regex);
			TRY_MATCH(ETokenType::RP);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::CHARSET);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::LEXERID);
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
			// EPSILON
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::PIPE);
			CALL_CHILD(Operatorr, Rule_operatorr);
			CALL_CHILD(Lexeror2, Rule_lexeror2);
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
			// EPSILON
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::PLUS);
			break;
		}
		case 2:
		{
			TRY_MATCH(ETokenType::QUESTIONMARK);
			break;
		}
		case 3:
		{
			TRY_MATCH(ETokenType::STAR);
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
			TRY_MATCH(ETokenType::PARSERID);
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::LP);
			CALL_CHILD(Parseror, Rule_parseror);
			TRY_MATCH(ETokenType::RP);
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
			// EPSILON
			break;
		}
		case 1:
		{
			CALL_CHILD(Parserconst, Rule_parserconst);
			CALL_CHILD(Parserlist, Rule_parserlist);
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
			// EPSILON
			break;
		}
		case 1:
		{
			TRY_MATCH(ETokenType::PIPE);
			CALL_CHILD(Parserlist, Rule_parserlist);
			CALL_CHILD(Parseror2, Rule_parseror2);
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
			// EPSILON
			break;
		}
		case 1:
		{
			CALL_CHILD(Lexeror, Rule_lexeror);
			CALL_CHILD(Regex, Rule_regex);
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
			TRY_MATCH(ETokenType::EOS);
			break;
		}
	}
	
	ExitRule(OutRule);
	return true;
}

const char* GrammarParser::GetSerializedTable() const
{
	return "0 4 1 0 12 0 1 3 3 1 6 2 1 9 0 1 10 4 1 16 1 2 3 0 2 6 0 2 9 0 2 10 0 2 16 0 3 3 0 3 4 0 3 6 0 3 9 0 3 10 0 3 12 0 3 14 1 3 15 0 3 16 0 4 3 0 5 3 0 5 6 0 5 9 0 5 10 0 5 16 0 6 3 0 6 4 0 6 5 2 6 6 0 6 7 3 6 8 1 6 9 0 6 10 0 6 12 0 6 14 0 6 15 0 6 16 0 7 3 2 7 10 3 7 11 0 7 16 1 8 3 1 8 10 1 8 11 1 8 12 0 8 14 0 8 15 0 8 16 1 9 3 0 9 10 0 9 11 0 9 12 0 9 14 0 9 15 0 9 16 0 10 12 0 10 14 1 10 15 0 11 11 0 12 3 1 12 4 0 12 6 1 12 9 1 12 10 1 12 12 0 12 15 0 12 16 1 13 -1 2 13 3 1 13 11 0 ";
}
