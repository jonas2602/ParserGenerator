#include "Alphabet.h"
#include <iostream>

namespace ParserGenerator {
	Alphabet::Alphabet(const std::map<std::string, int>& InTokens, const std::map<std::string, int>& InNonTerminals)
		:m_Tokens(InTokens), m_NonTerminals(InNonTerminals)
	{
		m_TokenList = std::vector<std::string>(InTokens.size());
		for (std::pair<std::string, int> Pair : InTokens)
		{
			m_TokenList[Pair.second] = Pair.first;
		}

		m_NonTerminalList = std::vector<std::string>(InNonTerminals.size());
		for (std::pair<std::string, int> Pair : InNonTerminals)
		{
			m_NonTerminalList[Pair.second] = Pair.first;
		}
	}

	Alphabet::Alphabet(const std::vector<std::string>& InTokens, const std::vector<std::string>& InNonTerminals)
		:m_TokenList(InTokens), m_NonTerminalList(InNonTerminals)
	{
		int TokenIndex = 0;
		for (const std::string& Token : InTokens)
		{
			m_Tokens[Token] = TokenIndex++;
		}

		int NonTerminalIndex = 0;
		for (const std::string& NonTerminal : InNonTerminals)
		{
			m_Tokens[NonTerminal] = NonTerminalIndex++;
		}
	}

	int Alphabet::GetTokenIndex(const std::string& TokenName) const
	{
		if (TokenName == "EOF") { return -1; }

		auto TokenPair = m_Tokens.find(TokenName);
		if (TokenPair == m_Tokens.end())
		{
			std::cout << "Can't find Index for '" << TokenName << "'" << std::endl;
			return -1;
		}

		return TokenPair->second;
	}

	int Alphabet::GetNonTerminalIndex(const std::string& NonTerminalName) const
	{
		auto NonTerminalPair = m_NonTerminals.find(NonTerminalName);
		if (NonTerminalPair == m_NonTerminals.end())
		{
			std::cout << "Can't find Index for '" << NonTerminalName << "'" << std::endl;
			return -1;
		}

		return NonTerminalPair->second;
	}

	std::string Alphabet::GetTokenName(int TokenId) const
	{
		if (TokenId == -1) { return "EOF"; }

		if (TokenId < 0 || TokenId >= m_TokenList.size())
		{
			std::cout << "Requested Token Index '" << TokenId << "' is out of Range" << std::endl;
			return "";
		}

		return m_TokenList[TokenId];
	}

	std::string Alphabet::GetNonTerminalName(int NonTerminalId) const
	{
		if (NonTerminalId < 0 || NonTerminalId >= m_NonTerminalList.size())
		{
			std::cout << "Requested Non Terminal Index '" << NonTerminalId << "' is out of Range" << std::endl;
			return "";
		}

		return m_NonTerminalList[NonTerminalId];
	}

	const std::vector<std::string>& Alphabet::GetTokenList() const
	{
		return m_TokenList;
	}

	const std::vector<std::string>& Alphabet::GetNonTerminalList() const
	{
		return m_NonTerminalList;
	}

	bool Alphabet::IsToken(const std::string& TokenName) const
	{
		return m_Tokens.find(TokenName) != m_Tokens.end();
	}
	
	bool Alphabet::IsNonTerminal(const std::string& NonTerminalName) const
	{
		return m_NonTerminals.find(NonTerminalName) != m_NonTerminals.end();
	}
}
