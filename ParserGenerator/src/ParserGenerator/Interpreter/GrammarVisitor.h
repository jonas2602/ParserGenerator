#pragma once

#include "GrammarParser/GrammarVisitorBase.h"
#include "LexerConfig.h"
#include "ParserConfig.h"

#include "RuleVisitor.h"
#include "TokenVisitor.h"

namespace ParserGenerator {

	class GrammarVisitor : public GrammarVisitorBase<bool>
	{
	protected:
		LexerConfig* m_LexerConfig;
		ParserConfig* m_ParserConfig;

		RuleVisitor* m_RuleVisitor;
		TokenVisitor* m_TokenVisitor;

	public:
		GrammarVisitor();
		~GrammarVisitor();

		LexerConfig* GetLexerConfig() const { return m_LexerConfig; }
		ParserConfig* GetParserConfig() const { return m_ParserConfig; }

		inline const std::vector<Node_PLACEHOLDER*>& GetPlaceholder() { return m_TokenVisitor->GetOpenPlaceholder(); }
		inline const std::map<std::string, RuleElement*>& GetLiteralMap() { return m_RuleVisitor->GetLiteralMap(); }
		inline const std::map<std::string, RuleElement*>& GetNonTerminalMap() { return m_RuleVisitor->GetNonTerminalMap(); }
		inline const std::map<std::string, RuleElement*>& GetTerminalMap() { return m_RuleVisitor->GetTerminalMap(); }

	public:
		// Inherited via TestVisitorBase
		virtual bool VisitRule_rulelist(Rule_rulelist* Context) override;
		virtual bool VisitRule_parserrule(Rule_parserrule* Context) override;
		virtual bool VisitRule_lexerrule(Rule_lexerrule* Context) override;

	protected:
		ELexerAction GetActionType(PC::TokenNode* ActionNode) const;
	};

}