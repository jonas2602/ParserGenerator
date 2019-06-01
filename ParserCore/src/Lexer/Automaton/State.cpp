#include "State.h"
#include "Transition.h"


namespace ParserCore::Automaton {
	State::State(const std::string& InStateName, int InPriority) 
		:m_StateName(InStateName), m_Priority(InPriority)
	{ }


	State::~State()
	{
	}
}