#pragma once

#include <string>
#include "Core.h"


namespace ParserGenerator {

	static const char EPSILON = '§';
	static const std::string EPSILON_S = "§";
	
	static bool IsEpsilon(const char& Symbol) { return Symbol == EPSILON; }
	static bool IsEpsilon(const std::string& Symbol) { return Symbol == EPSILON_S; }
}