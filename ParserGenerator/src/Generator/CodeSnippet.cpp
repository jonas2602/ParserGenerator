#include "CodeSnippet.h"

CodeSnippet_Base::CodeSnippet_Base(const int& InPriority, const std::vector<CodeSnippet_Base*> InChildSnippets)
	: m_Priority(InPriority), m_ChildSnippets(InChildSnippets)
{ }


CodeSnippet_Base::~CodeSnippet_Base()
{
}

void CodeSnippet_Base::GenerateChildren(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream) const
{
	for (CodeSnippet_Base* Child : m_ChildSnippets)
	{
		Child->Write(Writer, HeaderStream, SourceStream, this);
	}
}

void CodeSnippet_Include::Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const
{
	std::ofstream& UsedFile = m_bHeader ? HeaderStream : SourceStream;
	UsedFile << "#include ";
	UsedFile << (m_bIntern ? "\"" : "<");
	UsedFile << m_Path;
	UsedFile << (m_bIntern ? "\"" : ">");
	UsedFile << std::endl;
}

void CodeSnippet_Class::Write(IWriterInterface * Writer, std::ofstream & HeaderStream, std::ofstream & SourceStream, const CodeSnippet_Base * ParentSnippet) const
{
	HeaderStream << "class " << m_ClassName;
	if (m_ParentName.empty())
	{
		HeaderStream << std::endl;
	}
	else
	{
		HeaderStream << ": public " << m_ParentName << std::endl;
	}

	HeaderStream << "{" << std::endl;

	GenerateChildren(Writer, HeaderStream, SourceStream);

	HeaderStream << "};" << std::endl;
}

void CodeSnippet_Function::Write(IWriterInterface * Writer, std::ofstream & HeaderStream, std::ofstream & SourceStream, const CodeSnippet_Base * ParentSnippet) const
{
	// Declaration
	HeaderStream << "\t" << m_ReturnType << " " << m_FunctionName << "(";
	for (int i = 0; i < m_FunctionParameters.size(); i++)
	{
		if (i > 0) { HeaderStream << ", "; }
		HeaderStream << m_FunctionParameters[i];
	}
	HeaderStream << ")";

	if (m_bHeaderDefinition)
	{
		HeaderStream << std::endl;
		HeaderStream << "\t" << "{" << std::endl;
		for (const std::string& Line : m_FunctionBody)
		{
			HeaderStream << "\t\t" << Line;
		}
		HeaderStream << "\t" << "}" << std::endl;
	}
	else
	{
		HeaderStream << ";" << std::endl;

		SourceStream << m_ReturnType << " " << ((CodeSnippet_Class*)ParentSnippet)->GetClassName() << "::" << m_FunctionName << "(";
		for (int i = 0; i < m_FunctionParameters.size(); i++)
		{
			if (i > 0) { SourceStream << ", "; }
			SourceStream << m_FunctionParameters[i];
		}
		SourceStream << ")" << std::endl;
		SourceStream << "{" << std::endl;
		for (const std::string& Line : m_FunctionBody)
		{
			SourceStream << "\t" << Line << std::endl;
		}
		SourceStream << "}" << std::endl;
	}

	// Definition
}
