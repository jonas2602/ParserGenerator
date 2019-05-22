#pragma once

#include <vector>
#include <string>

#include "ParserConfig.h"
#include "ParseTree/ParseTree.h"
#include "ParseTree/RuleNode.h"
#include "../Lexer/Token.h"
#include "ParsingTable.h"
#include <stack>

namespace ParserGenerator {

	class Parser
	{
	protected:
		// ParserConfig* m_Config;
		ParsingTable* m_Table;
		const std::vector<Token*>& m_TokenStream;
		std::vector<Token*>::const_iterator m_TokenIterator;

		std::stack<RuleNode*> m_RuleStack;

	public:
		//Parser(ParserConfig* InConfig);
		Parser(const std::vector<Token*>& InTokenStream);
		~Parser();

		//ParserConfig* GetParserConfig() const { return m_Config; }
		ParsingTable* GetParsingTable() const { return m_Table; }

	protected:
		void LoadParsingTable();
		virtual std::string GetSerializedTable() const = 0;

		void EnterRule(RuleNode* Rule);
		void ExitRule(RuleNode* Rule);

		bool Match(int TokenType);
		int PredictProduction();
	};

}