#include "RuleNode.h"



namespace ParserGenerator {
	RuleNode::RuleNode()
	{
	}


	RuleNode::~RuleNode()
	{
	}

	ParseTree* RuleNode::GetParent() const
	{
		return nullptr;
	}

	ParseTree* RuleNode::GetChild(int Index) const
	{
		return m_Children[Index];
	}

	int RuleNode::GetChildCount() const
	{
		return m_Children.size();
	}

	void RuleNode::SetParent(ParseTree* InParent)
	{
	}

	std::vector<TokenNode*> RuleNode::GetTokens(const std::string& TokenType) const
	{
		std::vector<TokenNode*> OutTokens;
		for (ParseTree* Child : m_Children)
		{
			TokenNode* ChildToken = (TokenNode*)Child;
			if (ChildToken && ChildToken->IsTokenType(TokenType))
			{
				OutTokens.push_back(ChildToken);
			}
		}

		return OutTokens;
	}

	TokenNode* RuleNode::GetToken(const std::string& TokenType, int Index) const
	{
		// Index out of bounds
		if (Index < 0 || Index >= m_Children.size())
		{
			return nullptr;
		}

		int IteratorIndex = -1;
		for (ParseTree* Child : m_Children)
		{
			TokenNode* ChildToken = (TokenNode*)Child;
			if (ChildToken && ChildToken->IsTokenType(TokenType))
			{
				IteratorIndex++;
				if (IteratorIndex == Index)
				{
					return ChildToken;
				}
			}
		}

	}

	TokenNode* RuleNode::AddChild(Token* InToken)
	{
		TokenNode* OutNode = new TokenNode(InToken);
		OutNode->SetParent(this);
		m_Children.push_back(OutNode);

		return OutNode;
	}

	RuleNode* RuleNode::AddChild(RuleNode* InRuleNode)
	{
		m_Children.push_back(InRuleNode);
		InRuleNode->SetParent(this);

		return InRuleNode;
	}
}
