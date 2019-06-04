#pragma once

#include <vector>
#include <string>

#include "../Regex/RegExp.h"
#include <ParserCore.h>

namespace ParserGenerator {

	enum ELexerAction
	{
		DEFAULT,
		SKIP
	};

	struct TokenDefinition
	{
		std::string m_Name;
		RegExp* m_Expression;
		ELexerAction m_Action;

		TokenDefinition(const std::string& InName, RegExp* InExpression, ELexerAction InAction)
			: m_Name(InName), m_Expression(InExpression), m_Action(InAction)
		{ }

		TokenDefinition(const std::string& InName, ELexerAction InAction)
			: m_Name(InName), m_Expression(nullptr), m_Action(InAction)
		{ }

		~TokenDefinition()
		{
			delete m_Expression;
		}
	};

	class LexerConfig
	{
	protected:
		std::vector<TokenDefinition*> m_RegexList;
		std::vector<Node_PLACEHOLDER*> m_Placeholder;
		std::map<std::string, TokenDefinition*> m_TokenMap;

	public:
		LexerConfig();
		~LexerConfig();

		TokenDefinition* AddToken(const std::string& Name, RegExp* Expression, ELexerAction Action = ELexerAction::DEFAULT);

		bool FillPlaceholder(const std::vector<Node_PLACEHOLDER*>& InPlaceholder);
		void CreateLiterals(const std::map<std::string, struct RuleElement*>& InLiteralMap);

		bool HasDefinition(const std::string& TokenName) { return m_TokenMap.find(TokenName) != m_TokenMap.end(); }

		const std::vector<TokenDefinition*> GetRegexList() const { return m_RegexList; }
		TokenDefinition* GetConfigElementByIndex(int Index) const { return m_RegexList[Index]; }

		std::map<std::string, int> CreateTokenIndexMap() const;

		int GetDefinitionCount() const { return m_RegexList.size(); }
	};

}