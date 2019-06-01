#include "CodeSnippet.h"
#include <algorithm>

#include "FileTemplate.h"

namespace ParserCore {

	CodeSnippet_Base::CodeSnippet_Base(const int& InPriority, const std::vector<CodeSnippet_Base*> InChildSnippets)
		: m_Priority(InPriority), m_ChildSnippets(InChildSnippets), m_OwningFile(nullptr), m_ParentSnippet(nullptr)
	{ }

	CodeSnippet_Base::CodeSnippet_Base(const int& InPriority)
		: CodeSnippet_Base(InPriority, {})
	{ }


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

	void CodeSnippet_Base::TriggerWrite()
	{
		m_InitialHeaderSpaces = m_OwningFile->GetHeaderSpaces();
		m_InitialSourceSpaces = m_OwningFile->GetSourceSpaces();
		Write();
	}

	void CodeSnippet_Base::GenerateChildren() const
	{
		for (CodeSnippet_Base* Child : m_ChildSnippets)
		{
			Child->TriggerWrite();
		}
	}

	const std::string& CodeSnippet_Base::GetHeaderSpaces() const
	{
		return m_OwningFile->GetHeaderSpaces();
	}

	const std::string& CodeSnippet_Base::GetSourceSpaces() const
	{
		return m_OwningFile->GetSourceSpaces();
	}

	void CodeSnippet_Plain::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetTextStream();
		HeaderStream << m_TextStream.str();
	}

	void CodeSnippet_Include::Write() const
	{
		std::ofstream& UsedFile = m_bHeader ? m_OwningFile->GetHeaderStream() : m_OwningFile->GetSourceStream();
		UsedFile << "#include ";
		UsedFile << (m_bIntern ? "\"" : "<");
		UsedFile << m_Path;
		UsedFile << (m_bIntern ? "\"" : ">");
		UsedFile << std::endl;
	}

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
}