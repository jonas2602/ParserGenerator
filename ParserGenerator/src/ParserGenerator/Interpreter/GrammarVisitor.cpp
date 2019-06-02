#include "GrammarVisitor.h"
#include <iostream>

namespace ParserGenerator {

	GrammarVisitor::GrammarVisitor(LexerConfig* InLexerConfig, ParserConfig* InParserConfig)
		: m_LexerConfig(InLexerConfig), m_ParserConfig(InParserConfig)
	{
		m_TokenVisitor = new TokenVisitor();
		m_RuleVisitor = new RuleVisitor();
	}

	GrammarVisitor::~GrammarVisitor()
	{
		delete m_TokenVisitor;
		delete m_RuleVisitor;
	}

	bool GrammarVisitor::VisitRule_rulelist(Rule_rulelist* Context)
	{
		if (Context->parserrule())
		{
			VisitRule_parserrule(Context->parserrule());
		}
		if (Context->lexerrule())
		{
			VisitRule_lexerrule(Context->lexerrule());
		}

		if (Context->rulelist())
		{
			VisitRule_rulelist(Context->rulelist());
		}

		return true;
	}

	bool GrammarVisitor::VisitRule_parserrule(Rule_parserrule* Context)
	{
		const std::string& RuleName = Context->PARSERID()->GetText();
		std::cout << "Visit Rule: " << RuleName << std::endl;

		// Grab Rule Versions from Parse Tree
		std::set<std::vector<RuleElement*>> OutLists = m_RuleVisitor->Visit(Context->parseror());
		for (const std::vector<RuleElement*>& RuleVersion : OutLists)
		{
			// Add them to the Parser Configuration
			m_ParserConfig->AddProduction(RuleName, RuleVersion);
		}

		return false;
	}

	bool GrammarVisitor::VisitRule_lexerrule(Rule_lexerrule* Context)
	{
		const std::string& TokenName = Context->LEXERID()->GetText();
		std::cout << "Visit Token: " << TokenName << std::endl;

		// Grab Regex from Parse Tree
		Node_BASE* RootNode = m_TokenVisitor->Visit(Context->regex());
		if (!RootNode) return false;
		RegExp* OutRegex = new RegExp(RootNode);

		// Check for special action
		ELexerAction ActionType = GetActionType(Context->action()->PARSERID());

		// Add it to Lexer Config
		m_LexerConfig->AddToken(TokenName, OutRegex, ActionType);

		return true;
	}

	ELexerAction GrammarVisitor::GetActionType(PC::TokenNode* ActionNode) const
	{
		if (!ActionNode) return ELexerAction::DEFAULT;

		const std::string& ActionName = ActionNode->GetText();

		if (ActionName == "skip") return ELexerAction::SKIP;
		else return ELexerAction::DEFAULT;
	}

}