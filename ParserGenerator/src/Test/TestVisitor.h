#pragma once

#include "TestRules.h"
#include "../Parser/Visitor.h"

template<typename T>
class TestVisitor : public ParserGenerator::Visitor
{
public:
	virtual void VisitRule_parser(Rule_parserrule* rule) = 0;
	virtual void VisitRule_parseror(Rule_parseror* rule) = 0;
};

