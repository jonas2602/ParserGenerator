#include "ParseTree.h"



ParseTree::ParseTree()
	:m_RootNode(nullptr)
{
}


ParseTree::~ParseTree()
{
	delete m_RootNode;
}

ParseNode_Token* ParseTree::InsertTokenNode(ParseNode* Parent, Token* InToken)
{
	ParseNode_Token* NewNode = new ParseNode_Token(InToken);
	AddNodeToTree(Parent, NewNode);

	return NewNode;
}

ParseNode_Production* ParseTree::InsertProductionNode(ParseNode* Parent, ParserConfigElement* InProduction)
{
	ParseNode_Production* NewNode = new ParseNode_Production(InProduction);
	AddNodeToTree(Parent, NewNode);

	return NewNode;
}

void ParseTree::AddNodeToTree(ParseNode* Parent, ParseNode* Child)
{
	if (!Parent)
	{
		// ... Create root node
		m_RootNode = Child;
	}
	else
	{
		Parent->m_Children.push_back(Child);
	}
}