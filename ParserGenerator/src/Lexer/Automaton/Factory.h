#pragma once

#include <string>
#include "Automaton.h"

namespace ParserGenerator::Automaton {
	
	class Factory
	{
	public:
		static bool Serialize(DFA* Automaton, const std::string& FilePath);
		static bool Deserialize(DFA* OutAutomaton, const std::string& FilePath);
	};

}