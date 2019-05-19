#include "TokenNode.h"



namespace ParserGenerator {

	TokenNode::TokenNode(Token* InToken)
		:m_Token(InToken)
	{

	}


	TokenNode::~TokenNode()
	{
		delete m_Token;
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

	const std::string& TokenNode::GetTokenType() const
	{
		return m_Token->GetTokenType();
	}

	bool TokenNode::IsTokenType(const std::string& InTokenType) const
	{
		return m_Token->GetTokenType() == InTokenType;
	}

}