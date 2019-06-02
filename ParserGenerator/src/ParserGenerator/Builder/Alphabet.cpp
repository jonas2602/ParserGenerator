#include "Alphabet.h"
#include <iostream>

#include <ParserCore.h>

namespace ParserGenerator {
	Alphabet::Alphabet(const std::map<std::string, int>& InTokens, const std::map<std::string, int>& InRules)
		:m_TokenIndexMap(InTokens), m_RuleIndexMap(InRules)
	{
		// Make shure EOS Token is contained
		m_TokenIndexMap[PC::EOS_S] = PC::EOS;

		for (std::pair<std::string, int> Pair : m_TokenIndexMap)
		{
			m_TerminalNames.insert(Pair.first);
			m_TokenNameMap[Pair.second] = Pair.first;
		}

		for (std::pair<std::string, int> Pair : m_RuleIndexMap)
		{
			m_NonTerminalNames.insert(Pair.first);
			m_RuleNameMap[Pair.second] = Pair.first;
		}
	}

	int Alphabet::GetTokenIndex(const std::string& TokenName) const
	{
		// if (TokenName == "EOS") { return -1; }
		auto TokenPair = m_TokenIndexMap.find(TokenName);
		if (TokenPair == m_TokenIndexMap.end())
		{
			std::cout << "Can't find Index for Token '" << TokenName << "'" << std::endl;
			return -2;
		}

		return TokenPair->second;
	}

	int Alphabet::GetRuleIndex(const std::string& RuleName) const
	{
		auto RulePair = m_RuleIndexMap.find(RuleName);
		if (RulePair == m_RuleIndexMap.end())
		{
			std::cout << "Can't find Index for Rule '" << RuleName << "'" << std::endl;
			return -2;
		}

		return RulePair->second;
	}

	const std::string& Alphabet::GetTokenName(int TokenId) const
	{
		//if (PC::IsEOS(TokenId)) { return PC::EOS_S; }
		auto TokenPair = m_TokenNameMap.find(TokenId);
		if (TokenPair == m_TokenNameMap.end())
		{
			std::cout << "Requested Token Index '" << TokenId << "' is out of Range" << std::endl;
			return "";
		}

		return TokenPair->second;
	}

	const std::string& Alphabet::GetRuleName(int RuleId) const
	{
		auto RulePair = m_RuleNameMap.find(RuleId);
		if (RulePair == m_RuleNameMap.end())
		{
			std::cout << "Requested Rule Index '" << RuleId << "' is out of Range" << std::endl;
			return "";
		}

		return RulePair->second;
	}

	/*const std::vector<std::string>& Alphabet::GetTokenList() const
	{
		return m_TokenList;
	}

	const std::vector<std::string>& Alphabet::GetNonTerminalList() const
	{
		return m_NonTerminalList;
	}

	const std::map<std::string, int>& Alphabet::GetTokenMap() const
	{
		return m_Tokens;
	}

	const std::map<std::string, int>& Alphabet::GetNonTerminalMap() const
	{
		return m_NonTerminals;
	}

	bool Alphabet::IsToken(const std::string& TokenName) const
	{
		return m_Tokens.find(TokenName) != m_Tokens.end();
	}

	bool Alphabet::IsNonTerminal(const std::string& NonTerminalName) const
	{
		return m_NonTerminals.find(NonTerminalName) != m_NonTerminals.end();
	}*/
}
