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
