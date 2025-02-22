#pragma once

#include "../Parser/Parser.h"
#include "TestRules.h"


class TestParser : public ParserCore::Parser
{
public:
	TestParser(const std::vector<ParserCore::Token*>& TokenStream);
	~TestParser();

public:
	bool Rulelist(Rule_rulelist*& OutRule);

	bool Parserrule(Rule_parserrule*& OutRule);
	bool Parseror(Rule_parseror*& OutRule);
	bool Parseror2(Rule_parseror2*& OutRule);
	bool Parserlist(Rule_parserlist*& OutRule);
	//bool Parserlist2(Rule_parserlist2*& OutRule);
	bool Parserconst(Rule_parserconst*& OutRule);

	bool Lexerrule(Rule_lexerrule*& OutRule);
	bool Action(Rule_action*& OutRule);
	bool Regex(Rule_regex*& OutRule);
	bool Lexeror(Rule_lexeror*& OutRule);
	bool Lexeror2(Rule_lexeror2*& OutRule);
	bool Operator(Rule_operator*& OutRule);
	bool Operator2(Rule_operator2*& OutRule);
	bool Lexerconst(Rule_lexerconst*& OutRule);
	
protected:
	virtual const char* GetSerializedTable() const override;
};

