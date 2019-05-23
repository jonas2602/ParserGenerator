#pragma once

#include "TestVisitorBase.h"

class TestVisitor : public TestVisitorBase<int>
{
public:
	virtual int VisitRule_parserrule(Rule_parserrule* Context) override;
	virtual int VisitRule_parseror(Rule_parseror* Context) override;
	virtual int VisitRule_parseror2(Rule_parseror2* Context) override;
	virtual int VisitRule_parserlist(Rule_parserlist* Context) override;
	virtual int VisitRule_parserconst(Rule_parserconst* Context) override;
};

