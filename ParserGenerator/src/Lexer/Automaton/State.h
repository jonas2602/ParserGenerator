#pragma once

#include <string>
#include <vector>

#include "..//..//Core.h"

namespace ParserGenerator::Automaton {

	class PARSER_API Transition;

	class State
	{
	protected:
		std::string m_StateName;

		// prio <  0 -> no final state
		// prio >= 0 -> priority of final state
		int m_Priority;

		std::vector<Transition*> m_Transitions;

	public:
		State(const std::string& InStateName, int InPriority = -1);
		~State();

		inline const std::string& GetName() const { return m_StateName; }
		inline int GetStatePriority() const { return m_Priority; }
		inline void SetStatePriority(int InPriority) { m_Priority = InPriority; }

		const std::vector<Transition*>& GetTransitions() const { return m_Transitions; }

	public:
		void AddTransition(Transition* InTransition) { m_Transitions.push_back(InTransition); }
	};

}