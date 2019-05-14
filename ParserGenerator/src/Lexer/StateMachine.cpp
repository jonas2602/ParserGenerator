#include "StateMachine.h"

#include <sstream>

#include "RegExp.h"
#include "../Utils/Math.h"

namespace ParserGenerator {

	const std::string StateMachine::EPSILON_S = "§";



	void State::GetEpsilonHull(std::set<State*>& OutStates)
	{
		if (OutStates.find(this) != OutStates.end())
		{
			return;
		}

		OutStates.insert(this);

		for (Transition* Element : m_Transitions)
		{
			if (Element->GetCondition() == StateMachine::EPSILON)
			{
				Element->GetTargetState()->GetEpsilonHull(OutStates);
			}
		}
	}

	void State::GetAvailableSymbols(std::set<char>& OutSymbols)
	{
		for (Transition* Element : m_Transitions)
		{
			const char& Symbol = Element->GetCondition();
			if (Symbol != StateMachine::EPSILON)
			{
				OutSymbols.insert(Symbol);
			}
		}
	}

	std::set<State*> State::Step(const char& Symbol) const
	{
		std::set<State*> OutStates;
		for (Transition* Element : m_Transitions)
		{
			if (Element->GetCondition() == Symbol)
			{
				OutStates.insert(Element->GetTargetState());
			}
		}

		return OutStates;
	}

	StateMachine::StateMachine()
	{
	}


	StateMachine::~StateMachine()
	{
	}

	void StateMachine::AddStartState(State* StartState)
	{
		// State Valid?
		if (!StartState) return;

		// TODO: Check if state from this state machine
		m_StartStates.insert(StartState);
	}

	State* StateMachine::CreateNewState(const std::string& StateName, /*const bool& bFinal,*/ const int& Priority)
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
		State* Instance = new State(FinalName, /*bFinal,*/ Priority);
		m_StateMap[FinalName] = Instance;

		return Instance;
	}

	Transition* StateMachine::CreateNewTransition(State* StartState, State* EndState, const char& Condition)
	{
		// Create Transition
		Transition* Instance = new Transition(EndState, Condition);
		m_Transitions.push_back(Instance);

		// Add Transition to Start State
		StartState->AddTransition(Instance);

		return Instance;
	}

	std::set<State*> StateMachine::GetEpsilonHull(std::set<State*> InStates) const
	{
		std::set<State*> OutStates;
		for (State* Element : InStates)
		{
			Element->GetEpsilonHull(OutStates);
		}

		return OutStates;
	}

	void StateMachine::CreateDeterministic(StateMachine& OutDFA)
	{
		std::map<std::set<State*>, State*> DFA_Map;
		std::vector<std::set<State*>> UnhandledStates;

		// Create Epsilon Hull for starting State
		std::set<State*> EpsilonHull = GetEpsilonHull(m_StartStates);

		// Add Start State to DFA
		State* StartState = OutDFA.CreateNewState(CreateCombinedName(EpsilonHull), FindPrioritisedFinalState(EpsilonHull));
		OutDFA.AddStartState(StartState);
		DFA_Map[EpsilonHull] = StartState;
		UnhandledStates.push_back(EpsilonHull);

		while (UnhandledStates.size() > 0)
		{
			// Get Remaining State Combination
			std::set<State*> ActiveStateList = UnhandledStates.back();
			UnhandledStates.pop_back();
			State* DFA_State = DFA_Map[ActiveStateList];

			// Get all chars that can be used in this Epsilon Hull
			std::set<char> SymbolList;
			for (State* Element : ActiveStateList)
			{
				Element->GetAvailableSymbols(SymbolList);
			}

			for (const char& Symbol : SymbolList)
			{
				// Find all States that can be reached with this symbol
				std::set<State*> SymbolStep;
				for (State* ActiveState : ActiveStateList)
				{
					std::set<State*> ReachedStates = ActiveState->Step(Symbol);
					SymbolStep.insert(ReachedStates.begin(), ReachedStates.end());
				}

				// Add all states that can be reached with epsilon
				SymbolStep = GetEpsilonHull(SymbolStep);

				// Create Combined State in DFA if not already existing
				State* DFA_TargetState = DFA_Map[SymbolStep];
				if (!DFA_TargetState)
				{
					// Add Start State to DFA
					DFA_TargetState = OutDFA.CreateNewState(CreateCombinedName(SymbolStep), FindPrioritisedFinalState(SymbolStep));
					DFA_Map[SymbolStep] = DFA_TargetState;
					UnhandledStates.push_back(SymbolStep);
				}

				// Create Transition with given Symbol
				OutDFA.CreateNewTransition(DFA_State, DFA_TargetState, Symbol);
			}
		}
	}

	std::string StateMachine::CreateCombinedName(const std::set<State*>& States) const
	{
		std::stringstream ss;
		for (State* Element : States)
		{
			ss << Element->GetName() << "|";
		}

		return ss.str();
	}

	int StateMachine::FindPrioritisedFinalState(const std::set<State*>& States) const
	{
		int MaxPriority = -1;
		for (State* Element : States)
		{
			int StatePriority = Element->GetStatePriority();
			MaxPriority = Math::Max(MaxPriority, StatePriority);
		}

		return MaxPriority;
	}

}