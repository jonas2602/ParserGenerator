#include "TokenNode.h"
#include <iostream>



namespace ParserCore {

	TokenNode::TokenNode(Token* InToken)
		:m_Token(InToken), m_Parent(nullptr)
	{

	}


	TokenNode::~TokenNode()
	{
		// Tokens will be deleted by the using application
		// delete m_Token;
	}

	ParseTree* TokenNode::GetParent() const
	{
		return m_Parent;
	}

	ParseTree* TokenNode::GetChild(int Index) const
	{
		return nullptr;
	}

	int TokenNode::GetChildCount() const
	{
		return 0;
	}

	void TokenNode::SetParent(ParseTree* InParent)
	{
		m_Parent = InParent;
	}

	int TokenNode::GetTokenType() const
	{
		return m_Token->GetTokenType();
	}

	bool TokenNode::IsTokenType(int InTokenType) const
	{
		return m_Token->GetTokenType() == InTokenType;
	}

}