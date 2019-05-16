#pragma once

#include <string>
#include "Automaton.h"

namespace ParserGenerator::Automaton {
	
	class Factory
	{
	public:
		static void Serialize(DFA* Automaton, const std::string& FilePath);
		static void Deserialize(DFA* OutAutomaton, const std::string& FilePath);
	};

}