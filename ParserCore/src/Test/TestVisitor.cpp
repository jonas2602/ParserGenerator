#include "TestVisitor.h"
#include <iostream>

TestVisitor::TestVisitor()
{
	m_LexerConfig = new ParserCore::LexerConfig();
	m_ParserConfig = new ParserCore::ParserConfig();

	m_TokenVisitor = new TokenVisitor();
	m_RuleVisitor = new RuleVisitor();
}

TestVisitor::~TestVisitor()
{
	delete m_LexerConfig;
	delete m_ParserConfig;

	delete m_TokenVisitor;
	delete m_RuleVisitor;
}

bool TestVisitor::VisitRule_rulelist(Rule_rulelist* Context)
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

bool TestVisitor::VisitRule_parserrule(Rule_parserrule* Context)
{
	const std::string& RuleName = Context->PARSERID()->GetText();
	std::cout << "Visit Rule: " << RuleName << std::endl;

	// Grab Rule Versions from Parse Tree
	std::set<std::vector<std::string>> OutLists = m_RuleVisitor->Visit(Context->parseror());
	for (const std::vector<std::string>& RuleVersion : OutLists)
	{
		// Add them to the Parser Configuration
		m_ParserConfig->AddProduction(RuleName, RuleVersion);
	}

	return false;
}

bool TestVisitor::VisitRule_lexerrule(Rule_lexerrule* Context)
{
	const std::string& TokenName = Context->LEXERID()->GetText();
	std::cout << "Visit Token: " << TokenName << std::endl;

	// Grab Regex from Parse Tree
	ParserCore::Node_BASE* RootNode = m_TokenVisitor->Visit(Context->regex());
	if (!RootNode) return false;
	ParserCore::RegExp* OutRegex = new ParserCore::RegExp(RootNode);

	// Check for special action
	ParserCore::ELexerAction ActionType = GetActionType(Context->action()->PARSERID());

	// Add it to Lexer Config
	m_LexerConfig->Add(TokenName, OutRegex, ActionType);

	return true;
}

ParserCore::ELexerAction TestVisitor::GetActionType(ParserCore::TokenNode* ActionNode) const
{
	if (!ActionNode) return ParserCore::ELexerAction::DEFAULT;

	const std::string& ActionName = ActionNode->GetText();

	if (ActionName == "skip") return ParserCore::ELexerAction::SKIP;
	else return ParserCore::ELexerAction::DEFAULT;
}