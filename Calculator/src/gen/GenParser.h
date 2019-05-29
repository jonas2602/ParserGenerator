// Automatically generated File
#pragma once

#include "GenRules.h"
#include <Parser.h>

class GenParser: public ParserGenerator::Parser
{
public:
	GenParser(const std::vector<ParserGenerator::Token*>& TokenStream);

public:
	bool Action(Rule_action*& OutRule);
	bool Lexerconst(Rule_lexerconst*& OutRule);
	bool Lexeror(Rule_lexeror*& OutRule);
	bool Lexeror2(Rule_lexeror2*& OutRule);
	bool Lexerrule(Rule_lexerrule*& OutRule);
	bool Operatorr(Rule_operatorr*& OutRule);
	bool Operatorr2(Rule_operatorr2*& OutRule);
	bool Parserconst(Rule_parserconst*& OutRule);
	bool Parserlist(Rule_parserlist*& OutRule);
	bool Parseror(Rule_parseror*& OutRule);
	bool Parseror2(Rule_parseror2*& OutRule);
	bool Parserrule(Rule_parserrule*& OutRule);
	bool Regex(Rule_regex*& OutRule);
	bool Rulelist(Rule_rulelist*& OutRule);

protected:
	virtual const char* GetSerializedTable() const override;

};
