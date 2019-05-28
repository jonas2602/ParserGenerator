// Automatically generated File
#pragma once

#include "GenRules.h"
#include <Parser.h>

template<typename T>
class GenVisitorBase: public ParserGenerator::Visitor<T>
{
public:
	virtual T VisitRule_action(Rule_action* Context) { return T(); }
	virtual T VisitRule_lexerconst(Rule_lexerconst* Context) { return T(); }
	virtual T VisitRule_lexeror(Rule_lexeror* Context) { return T(); }
	virtual T VisitRule_lexeror2(Rule_lexeror2* Context) { return T(); }
	virtual T VisitRule_lexerrule(Rule_lexerrule* Context) { return T(); }
	virtual T VisitRule_operatorr(Rule_operatorr* Context) { return T(); }
	virtual T VisitRule_operatorr2(Rule_operatorr2* Context) { return T(); }
	virtual T VisitRule_parserconst(Rule_parserconst* Context) { return T(); }
	virtual T VisitRule_parserlist(Rule_parserlist* Context) { return T(); }
	virtual T VisitRule_parseror(Rule_parseror* Context) { return T(); }
	virtual T VisitRule_parseror2(Rule_parseror2* Context) { return T(); }
	virtual T VisitRule_parserrule(Rule_parserrule* Context) { return T(); }
	virtual T VisitRule_regex(Rule_regex* Context) { return T(); }
	virtual T VisitRule_rulelist(Rule_rulelist* Context) { return T(); }

public:
	template<typename U>
	T Visit(U* Context)
	{
		static_assert(false);
	}
	template<>
	T Visit<Rule_action>(Rule_action* Context) { return VisitRule_action(Context); }
	template<>
	T Visit<Rule_lexerconst>(Rule_lexerconst* Context) { return VisitRule_lexerconst(Context); }
	template<>
	T Visit<Rule_lexeror>(Rule_lexeror* Context) { return VisitRule_lexeror(Context); }
	template<>
	T Visit<Rule_lexeror2>(Rule_lexeror2* Context) { return VisitRule_lexeror2(Context); }
	template<>
	T Visit<Rule_lexerrule>(Rule_lexerrule* Context) { return VisitRule_lexerrule(Context); }
	template<>
	T Visit<Rule_operatorr>(Rule_operatorr* Context) { return VisitRule_operatorr(Context); }
	template<>
	T Visit<Rule_operatorr2>(Rule_operatorr2* Context) { return VisitRule_operatorr2(Context); }
	template<>
	T Visit<Rule_parserconst>(Rule_parserconst* Context) { return VisitRule_parserconst(Context); }
	template<>
	T Visit<Rule_parserlist>(Rule_parserlist* Context) { return VisitRule_parserlist(Context); }
	template<>
	T Visit<Rule_parseror>(Rule_parseror* Context) { return VisitRule_parseror(Context); }
	template<>
	T Visit<Rule_parseror2>(Rule_parseror2* Context) { return VisitRule_parseror2(Context); }
	template<>
	T Visit<Rule_parserrule>(Rule_parserrule* Context) { return VisitRule_parserrule(Context); }
	template<>
	T Visit<Rule_regex>(Rule_regex* Context) { return VisitRule_regex(Context); }
	template<>
	T Visit<Rule_rulelist>(Rule_rulelist* Context) { return VisitRule_rulelist(Context); }

};
