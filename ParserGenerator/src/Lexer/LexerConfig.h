#pragma once

#include <vector>
#include <string>

#include "RegExp.h"

namespace ParserGenerator {

	enum ELexerAction
	{
		DEFAULT,
		SKIP
	};

	struct LexerConfigElement
	{
		std::string m_Name;
		RegExp* m_Expression;
		ELexerAction m_Action;

		LexerConfigElement(std::string InName, RegExp* InExpression, ELexerAction InAction)
			: m_Name(InName), m_Expression(InExpression), m_Action(InAction)
		{ }
	};

	class LexerConfig
	{
	protected:
		std::vector<LexerConfigElement> m_RegexList;

	public:
		LexerConfig();
		~LexerConfig();

		void Add(const std::string& Name, RegExp* Expression, ELexerAction Action = ELexerAction::DEFAULT);

		std::vector<LexerConfigElement> GetRegexList() const { return m_RegexList; }
		const LexerConfigElement& GetConfigElementByIndex(int Index) const { return m_RegexList[Index]; }
	};

}