#include "EnumSnippet.h"

#include <algorithm>


namespace ParserGenerator {

	CodeSnippet_Enum::CodeSnippet_Enum(const std::string& InEnumName, const std::map<std::string, int>& InEnumEntries)
		: CodeSnippet_Base(2), m_EnumName(InEnumName)
	{
		for (const std::pair<std::string, int>& Pair : InEnumEntries)
		{
			m_Entries[Pair.second] = Pair.first;
		}
	}

	void CodeSnippet_Enum::AddPair(const std::string& InKey, int InValue)
	{
		m_Entries[InValue] = InKey;
	}

	void CodeSnippet_Enum::Write() const
	{
		std::ofstream& HeaderStream = GetOwningFile()->GetHeaderStream();
		HeaderStream << m_InitialHeaderSpaces << "enum " << m_EnumName << " { " << std::endl;
		for (const std::pair<int, std::string>& Pair : m_Entries)
		{
			std::string UpperCaseName = Pair.second;
			std::transform(UpperCaseName.begin(), UpperCaseName.end(), UpperCaseName.begin(), ::toupper);
			// TODO: Name toUpperCase
			HeaderStream << m_InitialHeaderSpaces << "\t" << UpperCaseName << " = " << Pair.first << ", " << std::endl;
		}
		HeaderStream << m_InitialHeaderSpaces << "};" << std::endl << std::endl;
	}

}