#include "LexerConfig.h"

#include <utility>

namespace ParserCore {

	LexerConfig::LexerConfig()
	{
	}


	LexerConfig::~LexerConfig()
	{
	}

	void LexerConfig::Add(const std::string& Name, RegExp* Expression, ELexerAction Action)
	{
		m_RegexList.insert(m_RegexList.begin(), LexerConfigElement(Name, Expression, Action));
	}

	std::map<std::string, int> LexerConfig::GetTokenMap() const
	{
		std::map<std::string, int> TokenMap;

		for (int i = 0; i < m_RegexList.size(); i++)
		{
			TokenMap[m_RegexList[i].m_Name] = i;
		}

		return TokenMap;
	}

}