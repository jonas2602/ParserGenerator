#include "SwitchSnippet.h"
#include "../FileTemplate.h"

namespace ParserCore {

	void CodeSnippet_Switch::AddCase(const std::string& InCondition, const std::vector<std::string>& InBody)
	{
		m_Cases[InCondition] = InBody;
	}

	void CodeSnippet_Switch::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << m_InitialHeaderSpaces << "switch (" << m_Statement << ")" << std::endl;
		HeaderStream << m_InitialHeaderSpaces << "{" << std::endl;

		for (const std::pair<std::string, std::vector<std::string>>& Pair : m_Cases)
		{

		}

		HeaderStream << m_InitialHeaderSpaces << "}" << std::endl;
	}

	std::vector<std::string> CodeSnippet_Switch::GetRawLines() const
	{
		std::vector<std::string> OutLines;
		OutLines.push_back("switch (" + m_Statement + ")");
		OutLines.push_back("{");

		for (const std::pair<std::string, std::vector<std::string>>& Pair : m_Cases)
		{
			OutLines.push_back("\tcase " + Pair.first + ":");
			OutLines.push_back("\t{");
			for (const std::string& Line : Pair.second)
			{
				OutLines.push_back("\t\t" + Line);
			}

			OutLines.push_back("\t\tbreak;");
			OutLines.push_back("\t}");
		}

		OutLines.push_back("}");
		return OutLines;
	}

}