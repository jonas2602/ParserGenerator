#pragma once

#include "TestVisitorBase.h"
#include "../Lexer/LexerConfig.h"
#include "../Parser/ParserConfig.h"

#include "RuleVisitor.h"
#include "TokenVisitor.h"

class TestVisitor : public TestVisitorBase<bool>
{
protected:
	ParserCore::LexerConfig* m_LexerConfig;
	ParserCore::ParserConfig* m_ParserConfig;

	RuleVisitor* m_RuleVisitor;
	TokenVisitor* m_TokenVisitor;

public:
	TestVisitor();
	~TestVisitor();

	ParserCore::LexerConfig* GetLexerConfig() const { return m_LexerConfig; }
	ParserCore::ParserConfig* GetParserConfig() const { return m_ParserConfig; }

public:
	// Inherited via TestVisitorBase
	virtual bool VisitRule_rulelist(Rule_rulelist* Context) override;
	virtual bool VisitRule_parserrule(Rule_parserrule* Context) override;
	virtual bool VisitRule_lexerrule(Rule_lexerrule* Context) override;

protected:
	ParserCore::ELexerAction GetActionType(ParserCore::TokenNode* ActionNode) const;
};

