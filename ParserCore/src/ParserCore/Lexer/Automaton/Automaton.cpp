#include "Automaton.h"

#include <sstream>
#include <deque>
#include <iostream>

#include "../../ParserTypes.h"

namespace ParserCore::Automaton {

	Automaton::Automaton()
	{
	}


	Automaton::~Automaton()
	{
		for (std::pair<std::string, State*> Pair : m_StateMap)
		{
			delete Pair.second;
		}
		m_StateMap.clear();

		for (Transition* Trans : m_Transitions)
		{
			delete Trans;
		}
		m_Transitions.clear();
	}


	State* Automaton::CreateNewState(const std::string& StateName, const int& Priority)
	{
		// Create Unique Name
		std::string FinalName = StateName;
		if (StateName.empty() || m_StateMap.find(StateName) != m_StateMap.end())
		{
			std::stringstream ss;
			ss << StateName << m_NameCounter++;
			FinalName = ss.str();
		}
		// Create new State, store in map
		State* Instance = new State(FinalName, Priority);
		m_StateMap[FinalName] = Instance;

		return Instance;
	}

	Transition* Automaton::CreateNewTransition(State* StartState, State* EndState, const std::set<char>& Condition)
	{
		if (!StartState || !EndState)
		{
			std::cout << "Can't create Transition because StartState or EndState are invalid" << std::endl;
		}

		// Create Transition
		Transition* Instance = new Transition(EndState, Condition);
		m_Transitions.push_back(Instance);

		// Add Transition to Start State
		StartState->AddTransition(Instance);

		return Instance;
	}

	Transition* Automaton::CreateNewTransition(const std::string& StartStateName, const std::string& EndStateName, const std::set<char>& Condition)
	{
		State* StartState = m_StateMap[StartStateName];
		State* EndState = m_StateMap[EndStateName];

		return CreateNewTransition(StartState, EndState, Condition);
	}

	void DFA::SetStartState(State* StartState)
	{
		// State Valid?
		if (!StartState) return;

		// TODO: Check if state from this state machine
		m_StartState = StartState;
	}

	void DFA::SetStartState(const std::string& StartStateName)
	{
		SetStartState(m_StateMap[StartStateName]);
	}

	State* DFA::Step(State* InState, const char& Symbol) const
	{
		for (Transition* Element : InState->GetTransitions())
		{
			if (Element->Check(Symbol))
			{
				return Element->GetTargetState();
			}
		}

		return nullptr;
	}

}