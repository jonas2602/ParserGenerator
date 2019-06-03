#include "NFA.h"
#include "../Utils/Math.h"
#include <sstream>

namespace ParserGenerator {

	void NFA::AddStartState(PCA::State* StartState)
	{
		// State Valid?
		if (!StartState) return;

		// TODO: Check if state from this state machine
		m_StartStates.insert(StartState);
	}

	std::set<PCA::State*> NFA::BuildEpsilonHull(const std::set<PCA::State*>& InStates) const
	{
		std::deque<PCA::State*> StateQueue(InStates.begin(), InStates.end());
		std::set<PCA::State*> OutStates = InStates;

		while (!StateQueue.empty())
		{
			// Get first element
			PCA::State* ActiveState = StateQueue[0];
			StateQueue.pop_front();

			for (PCA::Transition* Trans : ActiveState->GetTransitions())
			{
				// Was neighbour not already visited?
				PCA::State* TargetState = Trans->GetTargetState();
				if (Trans->Check(PC::EPSILON) && OutStates.find(TargetState) == OutStates.end())
				{
					StateQueue.push_back(TargetState);
					OutStates.insert(TargetState);
				}
			}
		}

		return OutStates;
	}

	std::set<PCA::State*> NFA::BuildEpsilonHull_Min(const std::set<PCA::State*>& InStates) const
	{
		std::deque<PCA::State*> StateQueue(InStates.begin(), InStates.end());
		std::set<PCA::State*> OutStates;

		while (!StateQueue.empty())
		{
			// Get first element
			PCA::State* ActiveState = StateQueue[0];
			StateQueue.pop_front();

			bool bEpsilonState = true;
			for (PCA::Transition* Trans : ActiveState->GetTransitions())
			{
				// Was neighbour not already visited?
				PCA::State* TargetState = Trans->GetTargetState();
				bool bEpsilonTransition = Trans->Check(PC::EPSILON);
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

	std::map<std::set<PCA::State*>, std::set<char>> NFA::BuildTransitionMap(const std::set<PCA::State*>& StateList) const
	{
		// create a map of states that can get reached with each available symbol
		std::map<char, std::set<PCA::State*>> CharMap;
		for (PCA::State* ActiveState : StateList)
		{
			for (PCA::Transition* Trans : ActiveState->GetTransitions())
			{
				for (const char& Symbol : Trans->GetCondition())
				{
					if (Symbol != PC::EPSILON)
					{
						CharMap[Symbol].insert(Trans->GetTargetState());
					}
				}
			}
		}

		// flip map to combine all symbols that lead to same combination of states
		std::map<std::set<PCA::State*>, std::set<char>> TransitionMap;
		for (const std::pair<char, std::set<PCA::State*>>& Pair : CharMap)
		{
			TransitionMap[Pair.second].insert(Pair.first);
		}

		return TransitionMap;
	}

	std::string NFA::CreateCombinedName(const std::set<PCA::State*>& States) const
	{
		std::stringstream ss;
		for (PCA::State* Element : States)
		{
			ss << Element->GetName() << "|";
		}

		return ss.str();
	}

	int NFA::FindPrioritisedFinalState(const std::set<PCA::State*>& States) const
	{
		int MaxPriority = -1;
		for (PCA::State* Element : States)
		{
			int StatePriority = Element->GetStatePriority();
			MaxPriority = Math::Max(MaxPriority, StatePriority);
		}

		return MaxPriority;
	}

	void NFA::CreateDFA(PCA::DFA*& OutDFA) const
	{
		std::map<std::set<PCA::State*>, PCA::State*> DFA_Map;
		std::deque<std::set<PCA::State*>> UnhandledStates;

		// Create Epsilon Hull for starting State
		std::set<PCA::State*> StartHull = BuildEpsilonHull(m_StartStates);

		// Add Start State to DFA
		PCA::State* StartState = OutDFA->CreateNewState(CreateCombinedName(StartHull), FindPrioritisedFinalState(StartHull));
		OutDFA->SetStartState(StartState);
		DFA_Map[StartHull] = StartState;
		UnhandledStates.push_back(StartHull);

		while (UnhandledStates.size() > 0)
		{
			// Get Remaining State Combination
			std::set<PCA::State*> ActiveStateList = UnhandledStates.front();
			UnhandledStates.pop_front();
			PCA::State* DFA_State = DFA_Map[ActiveStateList];

			// Build Power Set for all available Symbols and Transitions
			std::map<std::set<PCA::State*>, std::set<char>> TransitionMap = BuildTransitionMap(ActiveStateList);

			for (const std::pair<std::set<PCA::State*>, std::set<char>>& Pair : TransitionMap)
			{
				// Add all additional states that can be reached with epsilon
				std::set<PCA::State*> EpsilonHull = BuildEpsilonHull(Pair.first);

				// Create Combined State in DFA if not already existing
				PCA::State* DFA_TargetState = DFA_Map[EpsilonHull];
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