#include "TestVisitor.h"
#include <iostream>

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
