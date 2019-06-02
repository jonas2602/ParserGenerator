#pragma once

#include <string>
#include <vector>
#include <set>

#include "ParserConfig.h"
#include "GrammarParser/GrammarVisitorBase.h"

namespace ParserGenerator {

	class RuleVisitor : public GrammarVisitorBase<std::set<std::vector<RuleElement*>>>
	{
	protected:
		// Content -> Name
		std::map<std::string, RuleElement*> m_LiteralMap;
		std::map<std::string, RuleElement*> m_NonTerminalMap;
		std::map<std::string, RuleElement*> m_TerminalMap;

	public:
		virtual std::set<std::vector<RuleElement*>> VisitRule_parseror(Rule_parseror* Context) override;
		virtual std::set<std::vector<RuleElement*>> VisitRule_parseror2(Rule_parseror2* Context) override;
		virtual std::set<std::vector<RuleElement*>> VisitRule_parserlist(Rule_parserlist* Context) override;
		virtual std::set<std::vector<RuleElement*>> VisitRule_parserconst(Rule_parserconst* Context) override;

		const std::map<std::string, RuleElement*>& GetLiteralMap() { return m_LiteralMap; }
		const std::map<std::string, RuleElement*>& GetNonTerminalMap() { return m_NonTerminalMap; }
		const std::map<std::string, RuleElement*>& GetTerminalMap() { return m_TerminalMap; }
	};

}