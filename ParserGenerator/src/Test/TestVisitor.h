#pragma once

#include "TestVisitorBase.h"
#include "../Lexer/LexerConfig.h"
#include "../Parser/ParserConfig.h"

#include "RuleVisitor.h"
#include "TokenVisitor.h"

class TestVisitor : public TestVisitorBase<bool>
{
protected:
	ParserGenerator::LexerConfig* m_LexerConfig;
	ParserGenerator::ParserConfig* m_ParserConfig;

	RuleVisitor* m_RuleVisitor;
	TokenVisitor* m_TokenVisitor;

public:
	TestVisitor();
	~TestVisitor();

	ParserGenerator::LexerConfig* GetLexerConfig() const { return m_LexerConfig; }
	ParserGenerator::ParserConfig* GetParserConfig() const { return m_ParserConfig; }

public:
	// Inherited via TestVisitorBase
	virtual bool VisitRule_rulelist(Rule_rulelist* Context) override;
	virtual bool VisitRule_parserrule(Rule_parserrule* Context) override;
	virtual bool VisitRule_lexerrule(Rule_lexerrule* Context) override;

protected:
	ParserGenerator::ELexerAction GetActionType(ParserGenerator::TokenNode* ActionNode) const;
};

