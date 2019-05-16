#include "Transition.h"
#include "State.h"


namespace ParserGenerator::Automaton {
	Transition::Transition(State* InTargetState, const char& InSymbol)
		: Transition(InTargetState, std::set<char>({ InSymbol }))
	{ }

	Transition::Transition(State* InTargetState, const std::set<char>& InList)
		: m_TargetState(InTargetState)
	{
		m_Condition = InList;
	}

	Transition::~Transition()
	{ }

	bool Transition::Check(const char& InSymbol)
	{
		return m_Condition.find(InSymbol) != m_Condition.end();
	}

}
