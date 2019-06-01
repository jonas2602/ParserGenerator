#pragma once

#include "TestRules.h"
#include "../Parser/Visitor.h"

template<typename T>
class TestVisitorBase : public ParserCore::Visitor<T>
{
public:
	virtual T VisitRule_rulelist(Rule_rulelist* Context) { return T(); }

	virtual T VisitRule_parserrule(Rule_parserrule* Context) { return T(); }
	virtual T VisitRule_parseror(Rule_parseror* Context) { return T(); }
	virtual T VisitRule_parseror2(Rule_parseror2* Context) { return T(); }
	virtual T VisitRule_parserlist(Rule_parserlist* Context) { return T(); }
	virtual T VisitRule_parserconst(Rule_parserconst* Context) { return T(); }

	virtual T VisitRule_lexerrule(Rule_lexerrule* Context) { return T(); }
	virtual T VisitRule_action(Rule_action* Context) { return T(); }
	virtual T VisitRule_regex(Rule_regex* Context) { return T(); }
	virtual T VisitRule_lexeror(Rule_lexeror* Context) { return T(); }
	virtual T VisitRule_lexeror2(Rule_lexeror2* Context) { return T(); }
	virtual T VisitRule_operator(Rule_operator* Context) { return T(); }
	virtual T VisitRule_operator2(Rule_operator2* Context) { return T(); }
	virtual T VisitRule_lexerconst(Rule_lexerconst* Context) { return T(); }


	template<typename U>
	T Visit(U* Context)
	{
		static_assert(false);
	}

	template<>
	T Visit<Rule_rulelist>(Rule_rulelist* Context) { return VisitRule_rulelist(Context); }

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

	template<>
	T Visit<Rule_lexerrule>(Rule_lexerrule* Context) { return VisitRule_lexerrule(Context); }
	template<>
	T Visit<Rule_action>(Rule_action* Context) { return VisitRule_action(Context); }
	template<>
	T Visit<Rule_regex>(Rule_regex* Context) { return VisitRule_regex(Context); }
	template<>
	T Visit<Rule_lexeror>(Rule_lexeror* Context) { return VisitRule_lexeror(Context); }
	template<>
	T Visit<Rule_lexeror2>(Rule_lexeror2* Context) { return VisitRule_lexeror2(Context); }
	template<>
	T Visit<Rule_operator>(Rule_operator* Context) { return VisitRule_operator(Context); }
	template<>
	T Visit<Rule_operator2>(Rule_operator2* Context) { return VisitRule_operator2(Context); }
	template<>
	T Visit<Rule_lexerconst>(Rule_lexerconst* Context) { return VisitRule_lexerconst(Context); }

protected:
	//virtual void CreateFunctionMap() override;
};
