#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

namespace ParserGenerator {
	
	class Alphabet
	{
	protected:
		std::map<std::string, int> m_TokenIndexMap;
		std::map<std::string, int> m_RuleIndexMap;

		std::map<int, std::string> m_TokenNameMap;
		std::map<int, std::string> m_RuleNameMap;

		std::set<std::string> m_TerminalNames;
		std::set<std::string> m_NonTerminalNames;

	public:
		Alphabet(const std::map<std::string, int>& InTokens, const std::map<std::string, int>& InRules);

	public:
		int GetTokenIndex(const std::string& TokenName) const;
		int GetRuleIndex(const std::string& RuleName) const;

		int GetElementIndex(struct RuleElement* InElement) const;

		const std::string& GetTokenName(int TokenId) const;
		const std::string& GetRuleName(int RuleId) const;


		const std::set<std::string>& GetTerminalNames() const { return m_TerminalNames; }
		const std::set<std::string>& GetNonTerminalNames() const { return m_NonTerminalNames; }

		const std::map<int, std::string>& GetTokenNameMap() const { return m_TokenNameMap; }
		const std::map<int, std::string>& GetRuleNameMap() const { return m_RuleNameMap; }

		const std::map<std::string, int>& GetTokenIndexMap() const { return m_TokenIndexMap; }
		const std::map<std::string, int>& GetRuleIndexMap() const { return m_RuleIndexMap; }

		bool IsToken(const std::string& TokenName) const { return m_TokenIndexMap.find(TokenName) != m_TokenIndexMap.end(); }
		bool IsRule(const std::string& RuleName) const { return m_RuleIndexMap.find(RuleName) != m_RuleIndexMap.end(); }
	};
}
