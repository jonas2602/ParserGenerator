#include "ParseTree.h"



ParseTree::ParseTree()
{
}


ParseTree::~ParseTree()
{
	delete m_RootNode;
}

ParseNode* ParseTree::InsertNode(ParseNode* Parent, Token* Data)
{
	ParseNode* NewNode = new ParseNode(Data);
	// Tree is created?	
	if (!Parent)
	{
		// ... Create root node
		m_RootNode = NewNode;
	}
	else
	{
		Parent->m_Children.push_back(NewNode);
	}

	return NewNode;
}