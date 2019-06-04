#pragma once

#include <map>

#include "State.h"
#include "Transition.h"
#include "../../Core.h"

namespace ParserCore::Automaton {

	class PARSER_API Automaton
	{
	protected:
		std::map<std::string, State*> m_StateMap;
		std::vector<Transition*> m_Transitions;

		int m_NameCounter = 0;

	public:
		Automaton();
		virtual ~Automaton();

		const std::map<std::string, State*>& GetStateMap() const { return m_StateMap; }
		const std::vector<Transition*>& GetTransitions() const { return m_Transitions; }
		int GetStateCount() const { return (int)m_StateMap.size(); }

	public:
		State* CreateNewState(const std::string& StateName = "", const int& Priority = -1);
		Transition* CreateNewTransition(State* StartState, State* EndState, const std::set<char>& Condition);
		Transition* CreateNewTransition(const std::string& StartStateName, const std::string& EndStateName, const std::set<char>& Condition);
	};



	class PARSER_API DFA : public Automaton
	{
	protected:
		State* m_StartState;

	public:
		State* GetStartState() const { return m_StartState; }
		void SetStartState(State* StartState);
		void SetStartState(const std::string& StartStateName);

	public:
		State* Step(State* InState, const char& Symbol) const;
	};

}