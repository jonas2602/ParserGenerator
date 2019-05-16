#pragma once

#include <map>

#include "State.h"
#include "Transition.h"

namespace ParserGenerator::Automaton {
	class Factory;

	static const char EPSILON = '§';
	static const std::string EPSILON_S = "§";

	class Automaton
	{
	protected:
		std::map<std::string, State*> m_StateMap;
		std::vector<Transition*> m_Transitions;

		int m_NameCounter = 0;

	public:
		Automaton();
		~Automaton();

		State* CreateNewState(const std::string& StateName = "", const int& Priority = -1);
		Transition* CreateNewTransition(State* StartState, State* EndState, const std::set<char>& Condition);

		friend Factory;
	};



	class DFA : public Automaton 
	{
	protected:
		State* m_StartState;

	public:
		State* GetStartState() const { return m_StartState; }
		void SetStartState(State* StartState);

	public:
		State* Step(State* InState, const char& Symbol) const;
	};



	class NFA : public Automaton 
	{
	protected:
		std::set<State*> m_StartStates;

	public:
		std::set<State*> GetStartStates() const { return m_StartStates; }
		void AddStartState(State* StartState);

	protected:
		std::set<State*> BuildEpsilonHull(const std::set<State*>& InStates) const;
		std::set<State*> BuildEpsilonHull_Min(const std::set<State*>& InStates) const;

		// TODO: Optimize with ranges, ...
		std::map<std::set<State*>, std::set<char>> BuildTransitionMap(const std::set<State*>& StateList) const;

		std::string CreateCombinedName(const std::set<State*>& States) const;

		// -1 no final state, >= 0 index of prioritised regex with final state in this state
		int FindPrioritisedFinalState(const std::set<State*>& States) const;
	public:
		void CreateDFA(DFA*& OutDFA) const;
	};

}