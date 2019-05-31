#pragma once

#include <vector>
#include <string>

#include "RegExp.h"
#include "Token.h"

namespace ParserGenerator {

	enum ELexerAction
	{
		DEFAULT,
		SKIP
	};

	struct LexerConfigElement
	{
		std::string m_Name;
		RegExp* m_Expression; // Will be empty if deserialized from file
		ELexerAction m_Action;

		LexerConfigElement(const std::string& InName, RegExp* InExpression, ELexerAction InAction)
			: m_Name(InName), m_Expression(InExpression), m_Action(InAction)
		{ }

		LexerConfigElement(const std::string& InName, ELexerAction InAction)
			: m_Name(InName), m_Expression(nullptr), m_Action(InAction)
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

		const std::vector<LexerConfigElement>& GetRegexList() const { return m_RegexList; }
		const LexerConfigElement& GetConfigElementByIndex(int Index) const { return m_RegexList[Index]; }

		std::map<std::string, int> GetTokenMap() const;
	};

}