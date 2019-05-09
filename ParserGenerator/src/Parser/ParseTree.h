#pragma once

#include "../Lexer/Token.h"
#include <vector>

struct ParseNode
{
	std::vector<ParseNode*> m_Children;
	Token* m_Token;

	ParseNode(Token* InToken)
		:m_Token(InToken)
	{ }
};

class ParseTree
{
protected:
	ParseNode* m_RootNode;

public:
	ParseTree();
	~ParseTree();

	ParseNode* InsertNode(ParseNode* Parent, Token* Data);
};

