#include "CodeSnippet.h"
#include <iostream>
#include <algorithm>

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

	FileTemplate* CodeSnippet_Base::GetOwningFile() const
	{
		if (m_OwningFile)
		{
			return m_OwningFile;
		}
		else if (m_ParentSnippet)
		{
			return m_ParentSnippet->GetOwningFile();
		}
		else
		{
			std::cout << "no owning file or parent set" << std::endl;
			return nullptr;
		}
	}

	void CodeSnippet_Base::AttachSnippet(CodeSnippet_Base* InChild)
	{
		m_ChildSnippets.push_back(InChild);
		InChild->SetParent(this);
	}

	void CodeSnippet_Base::SetParent(CodeSnippet_Base* InParent)
	{
		m_ParentSnippet = InParent;
		SetOwningFile(InParent->m_OwningFile);
	}

	void CodeSnippet_Base::SetOwningFile(FileTemplate* InFile)
	{
		m_OwningFile = InFile;
	}

	void CodeSnippet_Base::AttachSnippet(const std::vector<CodeSnippet_Base*>& InChilden)
	{
		for (CodeSnippet_Base* Snippet : InChilden)
		{
			AttachSnippet(Snippet);
		}
	}

	void CodeSnippet_Base::TriggerWrite()
	{
		m_InitialHeaderSpaces = GetOwningFile()->GetHeaderSpaces();
		m_InitialSourceSpaces = GetOwningFile()->GetSourceSpaces();
		Write();
	}

	void CodeSnippet_Base::GenerateChildren() const
	{
		std::vector<CodeSnippet_Base*> OrderedChilds = m_ChildSnippets;

		// Sort Snippets by priority
		auto cmpLambda = [](CodeSnippet_Base* Left, CodeSnippet_Base* Right) {
			return Left->GetSnippetPriority() < Right->GetSnippetPriority();
		};
		std::sort(OrderedChilds.begin(), OrderedChilds.end(), cmpLambda);

		for (CodeSnippet_Base* Child : OrderedChilds)
		{
			Child->TriggerWrite();
		}
	}

	const std::string& CodeSnippet_Base::GetHeaderSpaces() const
	{
		return GetOwningFile()->GetHeaderSpaces();
	}

	const std::string& CodeSnippet_Base::GetSourceSpaces() const
	{
		return GetOwningFile()->GetSourceSpaces();
	}

}