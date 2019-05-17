#pragma once

#include <string>
#include <vector>
#include <set>

#include "../Core.h"
#include "Automaton/Automaton.h"

namespace ParserGenerator {

	class StateMachine;
	class State;


	class Node_BASE
	{
	public:
		virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) = 0;
		virtual void ExtendMachine(Automaton::NFA* OutMachine, Automaton::State*& OutStart, Automaton::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0) = 0;
	};

	class Node_CONST : public Node_BASE
	{
	protected:
		char m_Symbol;
		std::set<char> m_CharSet;

	public:
		Node_CONST(const char& InSymbol)
			: m_Symbol(InSymbol), m_CharSet({ InSymbol })
		{ }

		Node_CONST(const std::set<char>& InCharSet)
			: m_Symbol(' '), m_CharSet(InCharSet)
		{ }

		const std::set<char>& GetContent() const { return m_CharSet; }

		virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
		virtual void ExtendMachine(Automaton::NFA* OutMachine, Automaton::State*& OutStart, Automaton::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	};

	//class Node_RANGE : public Node_BASE
	//{
	//protected:
	//	char m_Min;
	//	char m_Max;
	//
	//public:
	//	Node_RANGE(const char& InMin, const char& InMax)
	//		: m_Min(InMin), m_Max(InMax)
	//	{}
	//
	//	virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	//};

	class Node_OR : public Node_BASE
	{
	protected:
		// Node_BASE* m_Left;
		// Node_BASE* m_Right;
		std::vector<Node_BASE*> m_Content;

	public:
		Node_OR(Node_BASE* InLeft, Node_BASE* InRight)
			: /*m_Left(InLeft), m_Right(InRight),*/ m_Content({ InLeft, InRight })
		{ }

		Node_OR(const std::vector<Node_BASE*>& InContent)
			: m_Content(InContent)
		{ }

		~Node_OR()
		{
			// delete m_Left;
			// delete m_Right;
		}

		virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
		virtual void ExtendMachine(Automaton::NFA* OutMachine, Automaton::State*& OutStart, Automaton::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	};

	class Node_AND : public Node_BASE
	{
	protected:
		//Node_BASE* m_Left;
		//Node_BASE* m_Right;
		std::vector<Node_BASE*> m_Content;

	public:
		Node_AND(Node_BASE* InLeft, Node_BASE* InRight)
			: /*m_Left(InLeft), m_Right(InRight),*/ m_Content({ InLeft, InRight })
		{ }

		Node_AND(const std::vector<Node_BASE*>& InContent)
			: m_Content(InContent)
		{ }

		~Node_AND()
		{
			//delete m_Left;
			//delete m_Right;
		}

		virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
		virtual void ExtendMachine(Automaton::NFA* OutMachine, Automaton::State*& OutStart, Automaton::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
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

		virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
		virtual void ExtendMachine(Automaton::NFA* OutMachine, Automaton::State*& OutStart, Automaton::State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	};

	//class Node_PLUS : public Node_BASE
	//{
	//protected:
	//	Node_BASE* m_Content;
	//
	//public:
	//	Node_PLUS(Node_BASE* InContent)
	//		: m_Content(InContent)
	//	{ }
	//
	//	~Node_PLUS()
	//	{
	//		delete m_Content;
	//	}
	//
	//	// Gets converted from x+ -> xx* 
	//	virtual void ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority = 0);
	//};



	class PARSER_API RegExp
	{
	public:
		// Special signs
		static const char TAB = '\t';	// Horizontal Tabulator
		static const char LF = '\n';	// Line Feed / New Line
		static const char CR = '\r';	// Carriage Return
		static const char ASCII_MIN = 32;
		static const char ASCII_MAX = 126;

	protected:
		Node_BASE* m_Root;

	public:
		RegExp(Node_BASE* InRoot);
		RegExp(const std::string& InString);
		~RegExp();

		void Parse(StateMachine& OutMachine, const std::string& Name, int Priority);
		void Parse(Automaton::NFA* OutMachine, const std::string& Name, int Priority);

	public:
		static Node_BASE* AND(const char& Left, const char& Right);
		static Node_BASE* AND(const char& Left, Node_BASE* Right);
		static Node_BASE* AND(Node_BASE* Left, const char& Right);
		static Node_BASE* AND(Node_BASE* Left, Node_BASE* Right);
		static Node_BASE* AND(const std::vector<char>& Content);
		static Node_BASE* AND(const std::vector<Node_BASE*>& Content);
		//static Node_BASE* AND(Node_BASE* Args, ...);

		static Node_BASE* OR(const char& Left, const char& Right);
		static Node_BASE* OR(const char& Left, Node_BASE* Right);
		static Node_BASE* OR(Node_BASE* Left, const char& Right);
		static Node_BASE* OR(Node_BASE* Left, Node_BASE* Right);
		static Node_BASE* OR(const std::vector<char>& Content);
		static Node_BASE* OR(const std::vector<Node_BASE*>& Content);

		static Node_BASE* STAR(const char& Content);
		static Node_BASE* STAR(Node_BASE* Content);

		// Internally converted from 'x+' -> 'xx*' 
		static Node_BASE* PLUS(const char& Content);
		static Node_BASE* PLUS(Node_BASE* Content);

		static Node_CONST* CONST(const char& Content);
		static Node_BASE* SEQUENCE(const std::string& Content);

		// Internally converted from '[min, max]' -> 'OR(min, ..., max)' 
		static Node_CONST* RANGE(const char& Min, const char& Max);

		static Node_CONST* LIST(const std::set<char>& Content);
		static Node_CONST* LIST(const std::vector<Node_CONST*>& Content);

		// Internally converted from '.' -> [32, 126] 
		static Node_BASE* ANY();

		static Node_BASE* EXCEPT(const std::vector<char>& Excluded);

		static Node_BASE* OPTIONAL(const char& Content);
		static Node_BASE* OPTIONAL(Node_BASE* Content);
	};

}