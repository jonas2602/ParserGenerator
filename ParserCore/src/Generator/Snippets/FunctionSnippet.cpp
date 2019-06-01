#include "FunctionSnippet.h"
#include "../FileTemplate.h"
#include "ClassSnippet.h"

namespace ParserCore {
	void CodeSnippet_Function::AddTemplating(const std::vector<std::string>& InTypeNames)
	{
		m_ModifierList.insert(TEMPLATE);
		m_TypeNames = InTypeNames;
	}

	void CodeSnippet_Function::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();

		if (IsTemplate())
		{
			HeaderStream << m_InitialHeaderSpaces << "template<";
			bool bFirst = true;
			for (const std::string& TypeName : m_TypeNames)
			{
				if (bFirst) {
					HeaderStream << "typename " << TypeName;
					bFirst = false;
				}
				else
				{
					HeaderStream << ", typename " << TypeName;
				}
			}
			HeaderStream << ">" << std::endl;
		}

		HeaderStream << m_InitialHeaderSpaces;
		if (IsStatic()) HeaderStream << "static ";
		if (IsVirtual()) HeaderStream << "virtual ";
		if (IsInline()) HeaderStream << "inline ";
		HeaderStream << m_ReturnType << " " << m_FunctionName << "(";
		for (int i = 0; i < m_FunctionParameters.size(); i++)
		{
			if (i > 0) { HeaderStream << ", "; }
			HeaderStream << m_FunctionParameters[i];
		}
		HeaderStream << ")";
		if (IsConstant()) HeaderStream << " const";
		if (IsOverride()) HeaderStream << " override";

		if (IsHeaderDefinition())
		{
			if (IsSingleLine())
			{
				HeaderStream << " { ";
				for (const std::string& Line : m_FunctionBody)
				{
					HeaderStream << Line;
				}
				HeaderStream << " }" << std::endl;
			}
			else
			{
				HeaderStream << std::endl;
				HeaderStream << m_InitialHeaderSpaces << "{" << std::endl;
				m_OwningFile->PushHeaderTab();
				for (const std::string& Line : m_FunctionBody)
				{
					HeaderStream << GetHeaderSpaces() << Line << std::endl;
				}
				m_OwningFile->PopHeaderTab();
				HeaderStream << m_InitialHeaderSpaces << "}" << std::endl;
			}
		}
		else
		{
			HeaderStream << ";" << std::endl;

			std::ofstream& SourceStream = m_OwningFile->GetSourceStream();
			SourceStream << std::endl;
			SourceStream << m_InitialSourceSpaces << m_ReturnType << " " << GetClassName() << "::" << m_FunctionName << CreateParameterString();
			if (IsConstant()) SourceStream << " const";
			SourceStream << std::endl;

			SourceStream << m_InitialSourceSpaces << "{" << std::endl;
			m_OwningFile->PushSourceTab();
			for (const std::string& Line : m_FunctionBody)
			{
				SourceStream << GetSourceSpaces() << Line << std::endl;
			}
			m_OwningFile->PopSourceTab();
			SourceStream << m_InitialSourceSpaces << "}" << std::endl;
		}

	}

	const std::string CodeSnippet_Function::GetClassName() const
	{
		CodeSnippet_Class* ParentClass = dynamic_cast<CodeSnippet_Class*>(m_ParentSnippet);
		if (ParentClass)
		{
			return ParentClass->GetClassName();
		}

		return "";
	}

	std::string CodeSnippet_Function::CreateParameterString() const
	{
		std::string ParameterString = "(";
		for (int i = 0; i < m_FunctionParameters.size(); i++)
		{
			if (i > 0) { ParameterString += ", "; }
			ParameterString += m_FunctionParameters[i];
		}
		ParameterString += ")";

		return ParameterString;
	}
}