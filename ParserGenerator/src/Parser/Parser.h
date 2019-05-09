#pragma once

#include <vector>
#include <string>

#include "ParserConfig.h"
#include "ParseTree.h"
#include "../Lexer/Token.h"
#include "ParsingTable.h"

class Parser
{
protected:
	ParserConfig* m_Config;
	ParsingTable* m_Table;

public:
	Parser(ParserConfig* InConfig);
	~Parser();

	ParseTree* BuildTree(std::vector<Token*> TokenStream);

protected:
	bool WalkProduction(const std::string& NonTerminal, std::vector<Token*>::iterator& TokenStream, ParseTree* OutTree, ParseNode* ParentNode);
};

