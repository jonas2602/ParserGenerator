#include "CodeSnippet.h"
#include <algorithm>

#include "FileTemplate.h"

namespace ParserGenerator {

	CodeSnippet_Base::CodeSnippet_Base(const int& InPriority, const std::vector<CodeSnippet_Base*> InChildSnippets)
		: m_Priority(InPriority), m_ChildSnippets(InChildSnippets)
	{ }

	CodeSnippet_Base::CodeSnippet_Base(const int& InPriority)
		: m_Priority(InPriority)
	{
	}


	CodeSnippet_Base::~CodeSnippet_Base()
	{
	}

	void CodeSnippet_Base::AttachSnippet(CodeSnippet_Base* InChild)
	{
		m_ChildSnippets.push_back(InChild);
		InChild->SetParent(this);
	}

	void CodeSnippet_Base::SetParent(CodeSnippet_Base* InParent)
	{
		m_ParentSnippet = InParent;
		SetOwningFile(InParent->GetOwningFile());
	}

	void CodeSnippet_Base::SetOwningFile(FileTemplate* InFile)
	{
		m_OwningFile = InFile;
	}

	void CodeSnippet_Base::GenerateChildren(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream) const
	{
		for (CodeSnippet_Base* Child : m_ChildSnippets)
		{
			Child->Write(Writer, HeaderStream, SourceStream, this);
		}
	}

	void CodeSnippet_Plain::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetTextStream();
		HeaderStream << m_TextStream.str();
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

	void CodeSnippet_Class::Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const
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

	void CodeSnippet_Function::Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const
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

	CodeSnippet_Enum::CodeSnippet_Enum(const std::string& InEnumName, const std::map<std::string, int>& InEnumEntries)
		: CodeSnippet_Base(1), m_EnumName(InEnumName)
	{
		for (const std::pair<std::string, int>& Pair : InEnumEntries)
		{
			m_Entries[Pair.second] = Pair.first;
		}
	}

	void CodeSnippet_Enum::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << "enum " << m_EnumName << " { " << std::endl;
		for (const std::pair<int, std::string>& Pair : m_Entries)
		{
			std::string UpperCaseName = Pair.second;
			std::transform(UpperCaseName.begin(), UpperCaseName.end(), UpperCaseName.begin(), ::toupper);
			// TODO: Name toUpperCase
			HeaderStream << "\t" << UpperCaseName << " = " << Pair.first << ", " << std::endl;
		}
		HeaderStream << "};" << std::endl << std::endl;
	}

	void CodeSnippet_Enum::Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const
	{
		HeaderStream << "enum " << m_EnumName << " { " << std::endl;
		for (const std::pair<int, std::string>& Pair : m_Entries)
		{
			std::string UpperCaseName = Pair.second;
			std::transform(UpperCaseName.begin(), UpperCaseName.end(), UpperCaseName.begin(), ::toupper);
			// TODO: Name toUpperCase
			HeaderStream << "\t" << UpperCaseName << " = " << Pair.first << ", " << std::endl;
		}
		HeaderStream << "};" << std::endl;
	}
}