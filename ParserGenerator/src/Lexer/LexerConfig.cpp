#include "LexerConfig.h"

#include <utility>

namespace ParserGenerator {

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

}