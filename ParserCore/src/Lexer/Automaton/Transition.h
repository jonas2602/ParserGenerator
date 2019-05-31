#pragma once

#include <set>


#include "..//..//Core.h"

namespace ParserGenerator::Automaton {
	class State;

	class Transition
	{
	protected:
		State* m_TargetState;
		
		// TODO: Three TransitionTypes
		// -> Single Character
		// -> Set of Characters
		// -> Range From Character to Character
		std::set<char> m_Condition;

	public:
		Transition(State* InTargetState, const char& InSymbol);
		Transition(State* InTargetState, const std::set<char>& InList);
		~Transition();

		inline const std::set<char>& GetCondition() const { return m_Condition; }
		inline State* GetTargetState() const { return m_TargetState; }

	public:
		bool Check(const char& InSymbol);
	};
}
