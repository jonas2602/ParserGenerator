#pragma once

#include <string>

class StringUtils
{
public:
	static std::string ToUpperCase(const std::string& InString);
	static std::string ToLowerCase(const std::string& InString);

	static std::string InterpretLiteral(const std::string& LiteralString);
	static char EscapeCharacter(const char& InCharacter);

};

