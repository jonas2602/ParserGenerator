#pragma once

#include "TestRules.h"
#include "../Parser/Visitor.h"

template<typename T>
class TestVisitorBase : public ParserGenerator::Visitor<T>
{
public:
	virtual T VisitRule_parserrule(Rule_parserrule* Context) = 0;
	virtual T VisitRule_parseror(Rule_parseror* Context) = 0;
	virtual T VisitRule_parseror2(Rule_parseror2* Context) = 0;
	virtual T VisitRule_parserlist(Rule_parserlist* Context) = 0;
	virtual T VisitRule_parserconst(Rule_parserconst* Context) = 0;

	template<typename U>
	T Visit(U* Context)
	{
		static_assert(false);
	}

	template<>
	T Visit<Rule_parserrule>(Rule_parserrule* Context) { return VisitRule_parserrule(Context); }
	template<>
	T Visit<Rule_parseror>(Rule_parseror* Context) { return VisitRule_parseror(Context); }
	template<>
	T Visit<Rule_parseror2>(Rule_parseror2* Context) { return VisitRule_parseror2(Context); }
	template<>
	T Visit<Rule_parserlist>(Rule_parserlist* Context) { return VisitRule_parserlist(Context); }
	template<>
	T Visit<Rule_parserconst>(Rule_parserconst* Context) { return VisitRule_parserconst(Context); }

protected:
	//virtual void CreateFunctionMap() override;
};
