#include "Automaton.h"

#include <sstream>
#include <deque>
#include <iostream>

#include "../../Utils/Math.h"
#include "../../ParserTypes.h"

namespace ParserGenerator::Automaton {

	Automaton::Automaton()
	{
	}


	Automaton::~Automaton()
	{
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

	void NFA::AddStartState(State* StartState)
	{
		// State Valid?
		if (!StartState) return;

		// TODO: Check if state from this state machine
		m_StartStates.insert(StartState);
	}

	std::set<State*> NFA::BuildEpsilonHull(const std::set<State*>& InStates) const
	{
		std::deque<State*> StateQueue(InStates.begin(), InStates.end());
		std::set<State*> OutStates = InStates;

		while (!StateQueue.empty())
		{
			// Get first element
			State* ActiveState = StateQueue[0];
			StateQueue.pop_front();

			for (Transition* Trans : ActiveState->GetTransitions())
			{
				// Was neighbour not already visited?
				State* TargetState = Trans->GetTargetState();
				if (Trans->Check(EPSILON) && OutStates.find(TargetState) == OutStates.end())
				{
					StateQueue.push_back(TargetState);
					OutStates.insert(TargetState);
				}
			}
		}

		return OutStates;
	}

	std::set<State*> NFA::BuildEpsilonHull_Min(const std::set<State*>& InStates) const
	{
		std::deque<State*> StateQueue(InStates.begin(), InStates.end());
		std::set<State*> OutStates;

		while (!StateQueue.empty())
		{
			// Get first element
			State* ActiveState = StateQueue[0];
			StateQueue.pop_front();

			bool bEpsilonState = true;
			for (Transition* Trans : ActiveState->GetTransitions())
			{
				// Was neighbour not already visited?
				State* TargetState = Trans->GetTargetState();
				bool bEpsilonTransition = Trans->Check(EPSILON);
				if (bEpsilonTransition && OutStates.find(TargetState) == OutStates.end())
				{
					StateQueue.push_back(TargetState);
					OutStates.insert(TargetState);
				}

				if (!bEpsilonTransition)
				{
					bEpsilonState = false;
				}
			}

			if (!bEpsilonState)
			{
				OutStates.insert(ActiveState);
			}
		}

		return OutStates;
	}

	std::map<std::set<State*>, std::set<char>> NFA::BuildTransitionMap(const std::set<State*>& StateList) const
	{
		// create a map of states that can get reached with each available symbol
		std::map<char, std::set<State*>> CharMap;
		for (State* ActiveState : StateList)
		{
			for (Transition* Trans : ActiveState->GetTransitions())
			{
				for (const char& Symbol : Trans->GetCondition())
				{
					if (Symbol != EPSILON)
					{
						CharMap[Symbol].insert(Trans->GetTargetState());
					}
				}
			}
		}

		// flip map to combine all symbols that lead to same combination of states
		std::map<std::set<State*>, std::set<char>> TransitionMap;
		for (const std::pair<char, std::set<State*>>& Pair : CharMap)
		{
			TransitionMap[Pair.second].insert(Pair.first);
		}

		return TransitionMap;
	}

	std::string NFA::CreateCombinedName(const std::set<State*>& States) const
	{
		std::stringstream ss;
		for (State* Element : States)
		{
			ss << Element->GetName() << "|";
		}

		return ss.str();
	}

	int NFA::FindPrioritisedFinalState(const std::set<State*>& States) const
	{
		int MaxPriority = -1;
		for (State* Element : States)
		{
			int StatePriority = Element->GetStatePriority();
			MaxPriority = Math::Max(MaxPriority, StatePriority);
		}

		return MaxPriority;
	}

	void NFA::CreateDFA(DFA*& OutDFA) const
	{
		std::map<std::set<State*>, State*> DFA_Map;
		std::deque<std::set<State*>> UnhandledStates;

		// Create Epsilon Hull for starting State
		std::set<State*> StartHull = BuildEpsilonHull(m_StartStates);

		// Add Start State to DFA
		State* StartState = OutDFA->CreateNewState(CreateCombinedName(StartHull), FindPrioritisedFinalState(StartHull));
		OutDFA->SetStartState(StartState);
		DFA_Map[StartHull] = StartState;
		UnhandledStates.push_back(StartHull);

		while (UnhandledStates.size() > 0)
		{
			// Get Remaining State Combination
			std::set<State*> ActiveStateList = UnhandledStates.front();
			UnhandledStates.pop_front();
			State* DFA_State = DFA_Map[ActiveStateList];

			// Build Power Set for all available Symbols and Transitions
			std::map<std::set<State*>, std::set<char>> TransitionMap = BuildTransitionMap(ActiveStateList);

			for (const std::pair<std::set<State*>, std::set<char>>& Pair : TransitionMap)
			{
				// Add all additional states that can be reached with epsilon
				std::set<State*> EpsilonHull = BuildEpsilonHull(Pair.first);

				// Create Combined State in DFA if not already existing
				State* DFA_TargetState = DFA_Map[EpsilonHull];
				if (!DFA_TargetState)
				{
					// Add New State to DFA
					DFA_TargetState = OutDFA->CreateNewState(CreateCombinedName(EpsilonHull), FindPrioritisedFinalState(EpsilonHull));
					DFA_Map[EpsilonHull] = DFA_TargetState;
					UnhandledStates.push_back(EpsilonHull);
				}

				// Create Transition with given Symbols
				OutDFA->CreateNewTransition(DFA_State, DFA_TargetState, Pair.second);
			}
		}
	}
}