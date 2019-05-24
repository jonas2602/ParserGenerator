#pragma once

#include "TestVisitorBase.h"

class TestVisitor : public TestVisitorBase<int>
{
public:
	virtual int VisitRule_rulelist(Rule_rulelist* Context) override;
	
	virtual int VisitRule_parserrule(Rule_parserrule* Context) override;
	virtual int VisitRule_parseror(Rule_parseror* Context) override;
	virtual int VisitRule_parseror2(Rule_parseror2* Context) override;
	virtual int VisitRule_parserlist(Rule_parserlist* Context) override;
	virtual int VisitRule_parserconst(Rule_parserconst* Context) override;

	virtual int VisitRule_(Rule_lexerrule* Context) override;
	virtual int VisitRule_parserconst(Rule_action* Context) override;
	virtual int VisitRule_regex(Rule_regex* Context) override;
	virtual int VisitRule_lexeror(Rule_lexeror* Context) override;
	virtual int VisitRule_lexeror2(Rule_lexeror2* Context) override;
	virtual int VisitRule_operator(Rule_operator* Context) override;
	virtual int VisitRule_operator2(Rule_operator2* Context) override;
	virtual int VisitRule_anytime(Rule_anytime* Context) override;
	virtual int VisitRule_once(Rule_once* Context) override;
	virtual int VisitRule_optional(Rule_optional* Context) override;
	virtual int VisitRule_lexerconst(Rule_lexerconst* Context) override;
};

