#pragma once

#include <vector>

#include "ParseTree.h"
#include "TokenNode.h"
#include "../../Core.h"

namespace ParserCore {
	class PARSER_API RuleNode : public ParseTree
	{
	protected:
		std::vector<ParseTree*> m_Children;

	public:
		RuleNode();
		~RuleNode();

		// Inherited via ParseTree
		virtual ParseTree* GetParent() const override;
		virtual ParseTree* GetChild(int Index) const override;
		virtual int GetChildCount() const override;
		virtual void SetParent(ParseTree* InParent) override;

	public:
		virtual int GetRuleType() const = 0;

	public:
		std::vector<TokenNode*> GetTokens(int TokenType) const;
		TokenNode* GetToken(int TokenType, int Index) const;

		template<typename T>
		T* GetRule(int Index) const;
		template<typename T>
		std::vector<T*> GetRules() const;

	public:
		TokenNode* AddChild(Token* InToken);
		RuleNode* AddChild(RuleNode* InRuleNode);

	};


	template<typename T>
	T* RuleNode::GetRule(int Index) const
	{
		// Index out of bounds
		if (Index < 0 || Index >= m_Children.size())
		{
			return nullptr;
		}

		int IteratorIndex = -1;
		for (ParseTree* Child : m_Children)
		{
			T* ChildRule = dynamic_cast<T*>(Child);
			if (ChildRule)
			{
				IteratorIndex++;
				if (IteratorIndex == Index)
				{
					return ChildRule;
				}
			}
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> RuleNode::GetRules() const
	{
		std::vector<T*> OutRules;
		for (ParseTree* Child : m_Children)
		{
			T* ChildRule = dynamic_cast<T*>(Child);
			if (ChildRule)
			{
				OutRules.push_back(ChildRule);
			}
		}

		return OutRules;
	}
}
