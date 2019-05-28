#include "FunctionSnippet.h"
#include "../FileTemplate.h"
#include "ClassSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_Function::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
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
			// if (!IsSingleLine()) HeaderStream << std::endl;
			HeaderStream << " { ";
			if (!IsSingleLine()) HeaderStream << std::endl;
			for (const std::string& Line : m_FunctionBody)
			{
				HeaderStream << Line;
				if (!IsSingleLine()) HeaderStream << std::endl;
			}
			HeaderStream << " }" << std::endl;
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

	// virtual int GetRuleType() const override { return ERuleType::RULELIST; }

	//void CodeSnippet_Function::Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const
	//{
	//	// Declaration
	//	HeaderStream << "\t" << m_ReturnType << " " << m_FunctionName << "(";
	//	for (int i = 0; i < m_FunctionParameters.size(); i++)
	//	{
	//		if (i > 0) { HeaderStream << ", "; }
	//		HeaderStream << m_FunctionParameters[i];
	//	}
	//	HeaderStream << ")";

	//	if (IsHeaderDefinition())
	//	{
	//		HeaderStream << std::endl;
	//		HeaderStream << "\t" << "{" << std::endl;
	//		for (const std::string& Line : m_FunctionBody)
	//		{
	//			HeaderStream << "\t\t" << Line;
	//		}
	//		HeaderStream << "\t" << "}" << std::endl;
	//	}
	//	else
	//	{
	//		HeaderStream << ";" << std::endl;

	//		SourceStream << m_ReturnType << " " << ((CodeSnippet_Class*)ParentSnippet)->GetClassName() << "::" << m_FunctionName << "(";
	//		for (int i = 0; i < m_FunctionParameters.size(); i++)
	//		{
	//			if (i > 0) { SourceStream << ", "; }
	//			SourceStream << m_FunctionParameters[i];
	//		}
	//		SourceStream << ")" << std::endl;
	//		SourceStream << "{" << std::endl;
	//		for (const std::string& Line : m_FunctionBody)
	//		{
	//			SourceStream << "\t" << Line << std::endl;
	//		}
	//		SourceStream << "}" << std::endl;
	//	}

	//	// Definition
	//}

}