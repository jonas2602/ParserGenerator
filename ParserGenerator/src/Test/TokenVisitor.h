#pragma once

#include "TestVisitorBase.h"
#include "../Lexer/RegExp.h"

class TokenVisitor : public TestVisitorBase<ParserGenerator::Node_BASE*>
{
public:
	virtual ParserGenerator::Node_BASE* VisitRule_action(Rule_action* Context) override;
	virtual ParserGenerator::Node_BASE* VisitRule_regex(Rule_regex* Context) override;
	virtual ParserGenerator::Node_BASE* VisitRule_lexeror(Rule_lexeror* Context) override;
	virtual ParserGenerator::Node_BASE* VisitRule_lexeror2(Rule_lexeror2* Context) override;
	virtual ParserGenerator::Node_BASE* VisitRule_operator(Rule_operator* Context) override;
	// virtual ParserGenerator::Node_BASE* VisitRule_operator2(Rule_operator2* Context) override;
	virtual ParserGenerator::Node_BASE* VisitRule_lexerconst(Rule_lexerconst* Context) override;
};

