#include <iostream>

#include "RegExp.h"
#include "StateMachine.h"
#include <algorithm>
#include <iterator>

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





	void Node_CONST::ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		//std::cout << "CONST:" << std::endl;

		OutStart = OutMachine.CreateNewState(Name);
		OutEnd = OutMachine.CreateNewState(Name, FinalStatePriority);

		//std::cout << OutStart->GetName() << std::endl;
		//std::cout << OutEnd->GetName() << std::endl;

		OutMachine.CreateNewTransition(OutStart, OutEnd, m_Symbol);
	}

	//void Node_RANGE::ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority)
	//{
	//	//std::cout << "RANGE:" << std::endl;
	//
	//	OutStart = OutMachine.CreateNewState(Name);
	//	OutEnd = OutMachine.CreateNewState(Name, FinalStatePriority);
	//
	//	//std::cout << OutStart->GetName() << std::endl;
	//	//std::cout << OutEnd->GetName() << std::endl;
	//
	//	//OutMachine.CreateNewTransition(OutStart, OutEnd, m_Symbol);
	//}

	void Node_OR::ExtendMachine(StateMachine& OutMachine, State*& OutStart, State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		//std::cout << "OR:" << std::endl;

		OutStart = OutMachine.CreateNewState(Name);
		OutEnd = OutMachine.CreateNewState(Name, FinalStatePriority);

		for (Node_BASE* Node : m_Content)
		{
			State* NodeStart;
			State* NodeEnd;
			Node->ExtendMachine(OutMachine, NodeStart, NodeEnd, Name, -1);
			OutMachine.CreateNewTransition(OutStart, NodeStart, StateMachine::EPSILON);
			OutMachine.CreateNewTransition(NodeEnd, OutEnd, StateMachine::EPSILON);
		}

		/*State* LeftStart;
		State* LeftEnd;
		m_Left->ExtendMachine(OutMachine, LeftStart, LeftEnd, Name, -1);
		OutMachine.CreateNewTransition(OutStart, LeftStart, StateMachine::EPSILON);
		OutMachine.CreateNewTransition(LeftEnd, OutEnd, StateMachine::EPSILON);

		State * RightStart;
		State * RightEnd;
		m_Right->ExtendMachine(OutMachine, RightStart, RightEnd, Name, -1);
		OutMachine.CreateNewTransition(OutStart, RightStart, StateMachine::EPSILON);
		OutMachine.CreateNewTransition(RightEnd, OutEnd, StateMachine::EPSILON);*/

		//std::cout << OutStart->GetName() << std::endl;
		//std::cout << OutEnd->GetName() << std::endl;
	}

	void Node_AND::ExtendMachine(StateMachine & OutMachine, State * &OutStart, State * &OutEnd, const std::string & Name, int FinalStatePriority)
	{
		//std::cout << "AND:" << std::endl;

		for (int i = 0; i < m_Content.size(); i++)
		{
			State* NodeStart;
			State* NodeEnd;
			m_Content[i]->ExtendMachine(OutMachine, NodeStart, NodeEnd, Name, -1);
			// First Element -> Set Global Start
			if (i == 0) OutStart = NodeStart;

			// Has Previous Element? -> Connect to Last
			if (i > 0) OutMachine.CreateNewTransition(OutEnd, NodeStart, StateMachine::EPSILON);

			// Update Global End
			OutEnd = NodeEnd;
		}
		/*State * LeftStart;
		State * LeftEnd;
		m_Left->ExtendMachine(OutMachine, LeftStart, LeftEnd, Name, -1);

		State * RightStart;
		State * RightEnd;
		m_Right->ExtendMachine(OutMachine, RightStart, RightEnd, Name, FinalStatePriority);

		OutMachine.CreateNewTransition(LeftEnd, RightStart, StateMachine::EPSILON);

		OutStart = LeftStart;
		OutEnd = RightEnd;*/
	}

	void Node_STAR::ExtendMachine(StateMachine & OutMachine, State * &OutStart, State * &OutEnd, const std::string & Name, int FinalStatePriority)
	{
		//std::cout << "STAR:" << std::endl;

		State* ContentStart;
		State* ContentEnd;
		m_Content->ExtendMachine(OutMachine, ContentStart, ContentEnd, Name, -1);

		OutStart = OutMachine.CreateNewState(Name);
		OutEnd = OutMachine.CreateNewState(Name, FinalStatePriority);

		//std::cout << OutStart->GetName() << std::endl;
		//std::cout << OutEnd->GetName() << std::endl;

		OutMachine.CreateNewTransition(ContentEnd, ContentStart, StateMachine::EPSILON);
		OutMachine.CreateNewTransition(OutStart, ContentStart, StateMachine::EPSILON);
		OutMachine.CreateNewTransition(ContentEnd, OutEnd, StateMachine::EPSILON);
		OutMachine.CreateNewTransition(OutStart, OutEnd, StateMachine::EPSILON);
	}

	//void Node_PLUS::ExtendMachine(StateMachine & OutMachine, State * &OutStart, State * &OutEnd, const std::string & Name, int FinalStatePriority)
	//{
	//	//std::cout << "STAR:" << std::endl;
	//
	//	State* ContentStart;
	//	State* ContentEnd;
	//	m_Content->ExtendMachine(OutMachine, ContentStart, ContentEnd, Name, -1);
	//
	//	OutStart = OutMachine.CreateNewState(Name);
	//	OutEnd = OutMachine.CreateNewState(Name, FinalStatePriority);
	//
	//	//std::cout << OutStart->GetName() << std::endl;
	//	//std::cout << OutEnd->GetName() << std::endl;
	//
	//	OutMachine.CreateNewTransition(ContentEnd, ContentStart, StateMachine::EPSILON);
	//	OutMachine.CreateNewTransition(OutStart, ContentStart, StateMachine::EPSILON);
	//	OutMachine.CreateNewTransition(ContentEnd, OutEnd, StateMachine::EPSILON);
	//	OutMachine.CreateNewTransition(OutStart, OutEnd, StateMachine::EPSILON);
	//}

	RegExp::RegExp(Node_BASE * InRoot)
		:m_Root(InRoot)
	{ }

	RegExp::RegExp(const std::string & InString)
		: m_Root(nullptr)
	{ }


	RegExp::~RegExp()
	{
		delete m_Root;
	}


	void RegExp::Parse(StateMachine & OutMachine, const std::string & Name, int Priority)
	{
		State* StartState;
		State* FinalState;
		m_Root->ExtendMachine(OutMachine, StartState, FinalState, Name, Priority);

		FinalState->SetStatePriority(Priority);
		OutMachine.AddStartState(StartState);
	}


	Node_BASE* RegExp::AND(const char& Left, const char& Right) { return RegExp::AND(new Node_CONST(Left), new Node_CONST(Right)); }
	Node_BASE* RegExp::AND(const char& Left, Node_BASE * Right) { return RegExp::AND(new Node_CONST(Left), Right); }
	Node_BASE* RegExp::AND(Node_BASE * Left, const char& Right) { return RegExp::AND(Left, new Node_CONST(Right)); }
	Node_BASE* RegExp::AND(Node_BASE * Left, Node_BASE * Right) { return new Node_AND(Left, Right); }
	Node_BASE* RegExp::AND(const std::vector<char> & Content) { return RegExp::AND(CreateNodeList(Content)); }
	Node_BASE* RegExp::AND(const std::vector<Node_BASE*> & Content) { return new Node_AND(Content); }

	Node_BASE* RegExp::OR(const char& Left, const char& Right) { return RegExp::OR(new Node_CONST(Left), new Node_CONST(Right)); }
	Node_BASE* RegExp::OR(const char& Left, Node_BASE * Right) { return RegExp::OR(new Node_CONST(Left), Right); }
	Node_BASE* RegExp::OR(Node_BASE * Left, const char& Right) { return RegExp::OR(Left, new Node_CONST(Right)); }
	Node_BASE* RegExp::OR(Node_BASE * Left, Node_BASE * Right) { return new Node_OR(Left, Right); }
	Node_BASE* RegExp::OR(const std::vector<char> & Content) { return RegExp::OR(CreateNodeList(Content)); }
	Node_BASE* RegExp::OR(const std::vector<Node_BASE*> & Content) { return new Node_OR(Content); }

	Node_BASE* RegExp::STAR(const char& Content) { return RegExp::STAR(new Node_CONST(Content)); }
	Node_BASE* RegExp::STAR(Node_BASE * Content) { return new Node_STAR(Content); }

	Node_BASE* RegExp::PLUS(const char& Content) { return RegExp::PLUS(new Node_CONST(Content)); }
	Node_BASE* RegExp::PLUS(Node_BASE * Content) { return RegExp::AND(Content, RegExp::STAR(Content)); }

	Node_BASE* RegExp::CONST(const char& Content) { return new Node_CONST(Content); }
	Node_BASE* RegExp::RANGE(const char& Min, const char& Max)
	{
		std::vector<Node_BASE*> OutNodes;
		for (int i = Min; i <= Max; i++)
		{
			OutNodes.push_back(new Node_CONST((char)i));
		}

		return RegExp::OR(OutNodes);
	}

	Node_BASE* RegExp::ANY() { return RegExp::RANGE(32, 126); }

}