#include "StringUtils.h"
#include <algorithm>

std::string StringUtils::ToUpperCase(const std::string& InString)
{
	std::string UpperCaseString = InString;
	std::transform(UpperCaseString.begin(), UpperCaseString.end(), UpperCaseString.begin(), ::toupper);
	return UpperCaseString;
}

std::string StringUtils::ToLowerCase(const std::string& InString)
{
	std::string LowerCaseString = InString;
	std::transform(LowerCaseString.begin(), LowerCaseString.end(), LowerCaseString.begin(), ::tolower);
	return LowerCaseString;
}

std::string StringUtils::InterpretLiteral(const std::string& LiteralString)
{
	std::string OutString = "";

	for (int i = 0; i < LiteralString.size(); i++)
	{
		if (LiteralString[i] == '\\')
		{
			// Move to the symbol that should get escaped
			i += 1;
			OutString += StringUtils::EscapeCharacter(LiteralString[i]);
		}
		else
		{
			OutString += LiteralString[i];
		}
	}

	return OutString;
}

char StringUtils::EscapeCharacter(const char& InCharacter)
{
	switch (InCharacter)
	{
		case 'a': return '\a';
		case 'b': return '\b';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';
		case 'v': return '\v';
		default: return InCharacter;
	}
}
