#include "ConstructorSnippet.h"
#include "ClassSnippet.h"
#include "../FileTemplate.h"

namespace ParserGenerator {

	void CodeSnippet_Constructor::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << m_InitialHeaderSpaces;
		HeaderStream << GetClassName() << CreateParameterString();

		if (m_bHeaderDefinition)
		{

		}
		else
		{
			HeaderStream << ";" << std::endl;

			std::ofstream& SourceStream = m_OwningFile->GetSourceStream();
			SourceStream << std::endl;
			SourceStream << m_InitialSourceSpaces << GetClassName() << "::" << GetClassName() << CreateParameterString() << std::endl;
			if (m_PreConstructorCalls.size() > 0)
			{
				SourceStream << m_InitialSourceSpaces << "\t: ";
				int Index = 0;
				for (const std::pair<std::string, std::string>& Pair : m_PreConstructorCalls)
				{
					if (Index > 0) { SourceStream << ", "; }

					SourceStream << Pair.first << "(" << Pair.second << ")";
					Index++;
				}

				SourceStream << std::endl;
			}

			SourceStream << m_InitialSourceSpaces << "{" << std::endl;
			m_OwningFile->PushSourceTab();
			for (const std::string& Line : m_ConstructorBody)
			{
				SourceStream << GetSourceSpaces() << Line << std::endl;
			}
			m_OwningFile->PopSourceTab();
			SourceStream << m_InitialSourceSpaces << "}" << std::endl;
		}
	}

	const std::string CodeSnippet_Constructor::GetClassName() const
	{
		CodeSnippet_Class* ParentClass = dynamic_cast<CodeSnippet_Class*>(m_ParentSnippet);
		if (ParentClass)
		{
			return ParentClass->GetClassName();
		}

		return "";
	}

	std::string CodeSnippet_Constructor::CreateParameterString() const
	{
		std::string ParameterString = "(";
		for (int i = 0; i < m_ConstructorParameters.size(); i++)
		{
			if (i > 0) { ParameterString += ", "; }
			ParameterString += m_ConstructorParameters[i];
		}
		ParameterString += ")";

		return ParameterString;
	}

}