#pragma once

#include "ParserCore.h"
#include "NFA.h"

namespace ParserGenerator {

	class Node_BASE
	{
	public:
		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) = 0;
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

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
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

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
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

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
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

		virtual void ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	};
}