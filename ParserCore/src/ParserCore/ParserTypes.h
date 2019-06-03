#pragma once

#include <string>
#include <vector>
#include "Core.h"


namespace ParserCore {

	static const char EPSILON = '§';
	static const std::string EPSILON_S = "§";
	
	static bool IsEpsilon(const char& Symbol) { return Symbol == EPSILON; }
	static bool IsEpsilon(const std::string& Symbol) { return Symbol == EPSILON_S; }
	static bool IsEpsilon(const std::vector<std::string>& Elements) { return std::find(Elements.begin(), Elements.end(), EPSILON_S) != Elements.end(); }

	static const std::string EOS_S = "EOS";
	static const int EOS = -1;
	static bool IsEOS(const std::string& TokenData) { return TokenData == EOS_S; }
	static bool IsEOS(int TokenType) { return TokenType == EOS; }
}