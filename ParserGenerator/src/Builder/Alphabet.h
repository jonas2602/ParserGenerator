#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

namespace ParserGenerator {
	class Alphabet
	{
	protected:
		std::map<std::string, int> m_Tokens;
		std::map<std::string, int> m_NonTerminals;

		std::vector<std::string> m_TokenList;
		std::vector<std::string> m_NonTerminalList;

	public:
		Alphabet(const std::map<std::string, int>& InTokens, const std::map<std::string, int>& InNonTerminals);
		Alphabet(const std::vector<std::string>& InTokens, const std::vector<std::string>& InNonTerminals);
	
	public:
		int GetTokenIndex(const std::string& TokenName) const;
		int GetNonTerminalIndex(const std::string& NonTerminalName) const;

		std::string GetTokenName(int TokenId) const;
		std::string GetNonTerminalName(int NonTerminalId) const;

		const std::vector<std::string>& GetTokenList() const;
		const std::vector<std::string>& GetNonTerminalList() const;

		bool IsToken(const std::string& TokenName) const;
		bool IsNonTerminal(const std::string& NonTerminalName) const;
	};
}
