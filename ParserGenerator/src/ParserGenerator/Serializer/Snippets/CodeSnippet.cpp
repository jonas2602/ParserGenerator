#include "CodeSnippet.h"

namespace ParserGenerator {

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

}