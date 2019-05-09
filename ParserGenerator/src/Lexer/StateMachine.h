#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>

class State;
class Transition;

class State {
protected:
	std::string m_StateName;
	//bool m_bFinalState;
	//  < 0 -> no final state
	// >= 0 -> priority of final state
	int m_Priority;

	std::vector<Transition*> m_Transitions;

public:
	State(const std::string& InStateName/*, bool InIsFinalState = false*/, int InPriority = -1)
		:m_StateName(InStateName)/*, m_bFinalState(InIsFinalState)*/, m_Priority(InPriority)
	{ }

	inline const std::string& GetName() const { return m_StateName; }

	//inline bool GetInFinalState() const { return m_bFinalState; }
	//inline void SetIsFinalState(bool InIsFinalState) { this->m_bFinalState = InIsFinalState; }

	inline int GetStatePriority() const { return m_Priority; }
	inline void SetStatePriority(int InPriority) { m_Priority = InPriority; }

public:
	void AddTransition(Transition* InTransition) { m_Transitions.push_back(InTransition); }

	// TODO: Add bHasFinalState as return value
	void GetEpsilonHull(std::set<State*>& OutStates);
	void GetAvailableSymbols(std::set<char>& OutSymbols);
	std::set<State*> Step(const char& Symbol) const;
};

class Transition {
protected:
	State* m_TargetState;
	char m_Condition;

public:
	Transition(State* InTargetState, char InCondition)
		: m_TargetState(InTargetState), m_Condition(InCondition)
	{ }

	inline const char& GetCondition() const { return m_Condition; }
	inline State* GetTargetState() const { return m_TargetState; }
};

class StateMachine
{
public:
	static const char EPSILON = '§';
	static const std::string EPSILON_S;

	static bool IsEpsilon(const char& Symbol) { return Symbol == EPSILON; }
	static bool IsEpsilon(const std::string& Symbol) { return Symbol == EPSILON_S; }

protected:
	std::map<std::string, State*> m_StateMap;
	std::vector<Transition*> m_Transitions;
	std::set<State*> m_StartStates;

	int m_NameCounter = 0;

public:
	StateMachine();
	~StateMachine();

	State* GetStateByName() const;
	std::set<State*> GetStartStates() const { return m_StartStates; }

	void AddStartState(State* StartState);

	State* CreateNewState(const std::string& StateName = ""/*, const bool& bFinal = false*/, const int& Priority = -1);
	Transition* CreateNewTransition(State* StartState, State* EndState, const char& Condition);

	std::set<State*> GetEpsilonHull(std::set<State*> InStates) const;

	void CreateDeterministic(StateMachine& OutDFA);

protected:
	std::string CreateCombinedName(const std::set<State*>& States) const;

	// -1 no final state, >= 0 index of prioritised regex with final state in this state
	int FindPrioritisedFinalState(const std::set<State*>& States) const;
};

