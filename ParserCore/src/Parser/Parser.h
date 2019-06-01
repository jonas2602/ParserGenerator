#pragma once

#include <vector>
#include <stack>
#include <string>

#include "ParserConfig.h"
#include "ParseTree/ParseTree.h"
#include "ParseTree/RuleNode.h"
#include "../Lexer/Token.h"
#include "ParseTable/ParsingTable.h"

#include "../Core.h"

#define TRY_MATCH(x) if(!Match(x)) return false; // std::cout << "Token mismatch, Expected: " << x << std::endl;
#define CALL_CHILD(func, type) { type* temp; if(!func(temp)) return false; }

namespace ParserCore {

	class PARSER_API Parser
	{
	protected:
		// ParserConfig* m_Config;
		ParseTable::ParsingTable* m_Table;
		const std::vector<Token*>& m_TokenStream;
		std::vector<Token*>::const_iterator m_TokenIterator;

		std::stack<RuleNode*> m_RuleStack;

	public:
		//Parser(ParserConfig* InConfig);
		Parser(const std::vector<Token*>& InTokenStream);
		~Parser();

		//ParserConfig* GetParserConfig() const { return m_Config; }
		ParseTable::ParsingTable* GetParsingTable() const { return m_Table; }

	protected:
		void LoadParsingTable();
		virtual const char* GetSerializedTable() const = 0;

		void EnterRule(RuleNode* Rule);
		void ExitRule(RuleNode* Rule);

		bool Match(int TokenType);
		int PredictProduction();
	};

}