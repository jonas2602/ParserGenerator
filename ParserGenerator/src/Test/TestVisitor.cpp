#include "TestVisitor.h"
#include <iostream>

int TestVisitor::VisitRule_rulelist(Rule_rulelist* Context)
{
	return 0;
}

int TestVisitor::VisitRule_parserrule(Rule_parserrule* Context)
{
	std::cout << "Visit Rule: " << Context->PARSERID()->GetText() << std::endl;

	return 0;
}

int TestVisitor::VisitRule_parseror(Rule_parseror* Context)
{
	return 0;
}

int TestVisitor::VisitRule_parseror2(Rule_parseror2* Context)
{
	return 0;
}

int TestVisitor::VisitRule_parserlist(Rule_parserlist* Context)
{
	return 0;
}

int TestVisitor::VisitRule_parserconst(Rule_parserconst* Context)
{
	return 0;
}


int TestVisitor::VisitRule_(Rule_lexerrule* Context)
{
	return 0;
}

int TestVisitor::VisitRule_parserconst(Rule_action* Context)
{
	return 0;
}

int TestVisitor::VisitRule_regex(Rule_regex* Context)
{
	return 0;
}

int TestVisitor::VisitRule_lexeror(Rule_lexeror* Context)
{
	return 0;
}

int TestVisitor::VisitRule_lexeror2(Rule_lexeror2* Context)
{
	return 0;
}

int TestVisitor::VisitRule_operator(Rule_operator* Context)
{
	return 0;
}

int TestVisitor::VisitRule_operator2(Rule_operator2* Context)
{
	return 0;
}

int TestVisitor::VisitRule_anytime(Rule_anytime* Context)
{
	return 0;
}

int TestVisitor::VisitRule_once(Rule_once* Context)
{
	return 0;
}

int TestVisitor::VisitRule_optional(Rule_optional* Context)
{
	return 0;
}

int TestVisitor::VisitRule_lexerconst(Rule_lexerconst* Context)
{
	return 0;
}
