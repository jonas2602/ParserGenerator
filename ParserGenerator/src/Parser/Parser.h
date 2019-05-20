#pragma once

#include <vector>
#include <string>

#include "ParserConfig.h"
#include "ParseTree/ParseTree.h"
#include "../Lexer/Token.h"
#include "ParsingTable.h"

namespace ParserGenerator {

	class Parser
	{
	protected:
		ParserConfig* m_Config;
		ParsingTable* m_Table;

	public:
		Parser(ParserConfig* InConfig);
		~Parser();

		ParserConfig* GetParserConfig() const { return m_Config; }
		ParsingTable* GetParsingTable() const { return m_Table; }

		ParseTree* BuildTree(std::vector<Token*> TokenStream);

	protected:
		bool WalkProduction(const std::string& NonTerminal, std::vector<Token*>::iterator& TokenStream, ParseTree* OutTree, ParseTree* ParentNode);
	};

}