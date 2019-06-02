#pragma once

#include "ParserCore.h"
#include "NFA.h"

namespace ParserGenerator {

	class Node_BASE
	{
	public:
		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const = 0;
	};

	class Node_CONST : public Node_BASE
	{
	protected:
		std::set<char> m_CharSet;

	public:
		Node_CONST(const char& InSymbol)
			: m_CharSet({ InSymbol })
		{ }

		Node_CONST(const std::set<char>& InCharSet)
			: m_CharSet(InCharSet)
		{ }

		const std::set<char>& GetContent() const { return m_CharSet; }
		bool IsSingleSymbol(char& OutSymbol) const 
		{
			if (m_CharSet.size() == 1)
			{
				OutSymbol = *m_CharSet.begin();
				return true;
			}
			return false;
		}

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const;
	};

	class Node_OR : public Node_BASE
	{
	protected:
		std::vector<Node_BASE*> m_Content;

	public:
		Node_OR(Node_BASE* InLeft, Node_BASE* InRight)
			: m_Content({ InLeft, InRight })
		{ }

		Node_OR(const std::vector<Node_BASE*>& InContent)
			: m_Content(InContent)
		{ }

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const;
	};

	class Node_AND : public Node_BASE
	{
	protected:
		std::vector<Node_BASE*> m_Content;

	public:
		Node_AND(Node_BASE* InLeft, Node_BASE* InRight)
			: m_Content({ InLeft, InRight })
		{ }

		Node_AND(const std::vector<Node_BASE*>& InContent)
			: m_Content(InContent)
		{ }

		const std::vector<Node_BASE*>& GetContent() const { return m_Content; }
		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const;
	};

	class Node_STAR : public Node_BASE
	{
	protected:
		Node_BASE* m_Content;

	public:
		Node_STAR(Node_BASE* InContent)
			: m_Content(InContent)
		{ }

		~Node_STAR()
		{
			delete m_Content;
		}

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const;
	};

	class Node_PLACEHOLDER : public Node_BASE
	{
	protected:
		std::string m_TerminalName;
		Node_BASE* m_FilledNode; // no need to delete, because it will be done by RegExp Object that contains this the filled node as root

	public:
		Node_PLACEHOLDER(const std::string& InTerminalName)
			: m_TerminalName(InTerminalName), m_FilledNode(nullptr)
		{ }

		const std::string& GetTerminalName() const { return m_TerminalName; }

		void FillPlaceholder(Node_BASE* InNode)
		{
			m_FilledNode = InNode;
		}

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) const;
	};
}