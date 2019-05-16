#include "Factory.h"
#include <sstream>

namespace ParserGenerator::Automaton {

	void Factory::Serialize(DFA* Automaton, const std::string& FilePath)
	{
		std::stringstream ss;

		// Serialize States
		for (const std::pair<std::string, State*>& Element : Automaton->m_StateMap)
		{

		}

		// Serialize Transitions
		
	}

	void Factory::Deserialize(DFA* OutAutomaton, const std::string& FilePath)
	{

	}

}