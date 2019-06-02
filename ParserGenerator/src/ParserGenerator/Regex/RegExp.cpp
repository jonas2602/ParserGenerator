#include <iostream>
#include <algorithm>
#include <iterator>

#include "RegExp.h"

namespace ParserGenerator {

	// Helper
	std::vector<Node_BASE*> CreateNodeList(const std::vector<char>& SymbolList)
	{
		std::vector<Node_BASE*> OutNodes;
		for (const char& Symbol : SymbolList)
		{
			OutNodes.push_back(new Node_CONST(Symbol));
		}
		// std::transform(Content.begin(), Content.end(), std::back_inserter(OutNodes), [](const char& Symbol) {return new Node_CONST(Symbol); });

		return OutNodes;
	}

	RegExp::RegExp(Node_BASE* InRoot)
		: m_Root(InRoot)
	{ }

	RegExp::RegExp(const std::string& InString)
		: m_Root(nullptr)
	{ }


	RegExp::~RegExp()
	{
		delete m_Root;
	}


	void RegExp::Parse(NFA* OutMachine, const std::string& Name, int Priority)
	{
		PCA::State* StartState;
		PCA::State* FinalState;
		m_Root->ExtendMachine(OutMachine, StartState, FinalState, Name, Priority);

		FinalState->SetStatePriority(Priority);
		OutMachine->AddStartState(StartState);
	}

	bool RegExp::IsLiteral(std::string& OutLiteral) const
	{
		// Is only a single Character?
		Node_CONST* RootConst = dynamic_cast<Node_CONST*>(m_Root);
		if (RootConst)
		{
			char OutSymbol;
			if (RootConst->IsSingleSymbol(OutSymbol))
			{
				OutLiteral = OutSymbol;
				return true;
			}
		}

		// Is a sequence of characters?
		Node_AND* RootAnd = dynamic_cast<Node_AND*>(m_Root);
		if (!RootAnd)
		{
			return false;
		}

		for (Node_BASE* Child : RootAnd->GetContent())
		{
			// ... therefore no other childs except of Node_CONST with a single symbol allowed 
			char OutSymbol;
			Node_CONST* ConstChild = dynamic_cast<Node_CONST*>(Child);
			if (!ConstChild || !ConstChild->IsSingleSymbol(OutSymbol))
			{
				return false;
			}

			OutLiteral += OutSymbol;
		}

		return true;
	}


	Node_BASE* RegExp::AND(const char& Left, const char& Right) { return RegExp::AND(new Node_CONST(Left), new Node_CONST(Right)); }
	Node_BASE* RegExp::AND(const char& Left, Node_BASE* Right) { return RegExp::AND(new Node_CONST(Left), Right); }
	Node_BASE* RegExp::AND(Node_BASE* Left, const char& Right) { return RegExp::AND(Left, new Node_CONST(Right)); }
	Node_BASE* RegExp::AND(Node_BASE* Left, Node_BASE* Right) { return new Node_AND(Left, Right); }
	Node_BASE* RegExp::AND(const std::vector<char>& Content) { return RegExp::AND(CreateNodeList(Content)); }
	Node_BASE* RegExp::AND(const std::vector<Node_BASE*>& Content)
	{
		if (Content.size() == 1)
			return Content[0];
		else
			return new Node_AND(Content);
	}

	Node_BASE* RegExp::OR(const char& Left, const char& Right) { return RegExp::OR(new Node_CONST(Left), new Node_CONST(Right)); }
	Node_BASE* RegExp::OR(const char& Left, Node_BASE* Right) { return RegExp::OR(new Node_CONST(Left), Right); }
	Node_BASE* RegExp::OR(Node_BASE* Left, const char& Right) { return RegExp::OR(Left, new Node_CONST(Right)); }
	Node_BASE* RegExp::OR(Node_BASE* Left, Node_BASE* Right) { return new Node_OR(Left, Right); }
	Node_BASE* RegExp::OR(const std::vector<char>& Content) { return RegExp::OR(CreateNodeList(Content)); }
	Node_BASE* RegExp::OR(const std::vector<Node_BASE*>& Content) { return new Node_OR(Content); }

	Node_BASE* RegExp::STAR(const char& Content) { return RegExp::STAR(new Node_CONST(Content)); }
	Node_BASE* RegExp::STAR(Node_BASE* Content) { return new Node_STAR(Content); }

	Node_BASE* RegExp::PLUS(const char& Content) { return RegExp::PLUS(new Node_CONST(Content)); }
	Node_BASE* RegExp::PLUS(Node_BASE* Content) { return RegExp::AND(Content, RegExp::STAR(Content)); }

	Node_CONST* RegExp::CONST(const char& Content) { return new Node_CONST(Content); }
	Node_BASE* RegExp::SEQUENCE(const std::string& Content)
	{
		std::vector<Node_BASE*> SequenceNodes;
		for (const char& Symbol : Content)
		{
			SequenceNodes.push_back(RegExp::CONST(Symbol));
		}

		return RegExp::AND(SequenceNodes);
	}

	Node_CONST* RegExp::RANGE(const char& Min, const char& Max)
	{
		std::vector<Node_BASE*> OutNodes;
		std::set<char> OutConst;
		for (char i = Min; i <= Max; i++)
		{
			//OutNodes.push_back(new Node_CONST(i));
			OutConst.insert(i);
		}

		// return RegExp::OR(OutNodes);
		return new Node_CONST(OutConst);
	}

	Node_CONST* RegExp::LIST(const std::set<char>& Content) { return new Node_CONST(Content); }
	Node_CONST* RegExp::LIST(const std::vector<Node_CONST*>& Content)
	{
		std::set<char> NewContent;
		for (Node_CONST* Element : Content)
		{
			NewContent.insert(Element->GetContent().begin(), Element->GetContent().end());
		}

		return new Node_CONST(NewContent);
	}

	Node_BASE* RegExp::ANY() { return RegExp::RANGE(ASCII_MIN, ASCII_MAX); }

	Node_BASE* RegExp::EXCEPT(const std::vector<char>& Excluded)
	{
		// TODO: Optimize, e.g. sort and walk indices to ignore (take care of duplicates)

		std::vector<Node_BASE*> OutNodes;
		std::set<char> OutConst;
		for (int i = ASCII_MIN; i <= ASCII_MAX; i++)
		{
			if (std::find(Excluded.begin(), Excluded.end(), i) == Excluded.end())
			{
				//OutNodes.push_back(new Node_CONST((char)i));
				OutConst.insert(i);
			}
		}

		//return RegExp::OR(OutNodes);
		return new Node_CONST(OutConst);
	}

	Node_BASE* RegExp::EXCEPT(const std::vector<Node_CONST*>& Excluded)
	{
		std::set<char> ExcludedChars;
		for (Node_CONST* ExcludeNode : Excluded)
		{
			ExcludedChars.insert(ExcludeNode->GetContent().begin(), ExcludeNode->GetContent().end());
		}

		return RegExp::EXCEPT(std::vector<char>(ExcludedChars.begin(), ExcludedChars.end()));
	}

	Node_BASE* RegExp::OPTIONAL(const char& Content) { return RegExp::OPTIONAL(new Node_CONST(Content)); }
	Node_BASE* RegExp::OPTIONAL(Node_BASE* Content) { return RegExp::OR(Content, PC::EPSILON); }

	Node_PLACEHOLDER* RegExp::PLACEHOLDER(const std::string& TerminalName)
	{
		return new Node_PLACEHOLDER(TerminalName);
	}
}