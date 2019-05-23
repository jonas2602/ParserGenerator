#pragma once

#include "../Parser/Parser.h"
#include "TestRules.h"
#include "../Lexer/Token.h"


class TestParser : public ParserGenerator::Parser
{
public:
	TestParser(const std::vector<ParserGenerator::Token*>& TokenStream);
	~TestParser();

	bool Parserrule(Rule_parserrule*& OutRule);
	bool Parseror(Rule_parseror*& OutRule);
	bool Parseror2(Rule_parseror2*& OutRule);
	bool Parserlist(Rule_parserlist*& OutRule);
	//bool Parserlist2(Rule_parserlist2*& OutRule);
	bool Parserconst(Rule_parserconst*& OutRule);

protected:
	virtual std::string GetSerializedTable() const override;
};

