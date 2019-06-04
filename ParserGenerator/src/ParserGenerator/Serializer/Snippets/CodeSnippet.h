#pragma once

#include "../WriterInterface.h"
#include "../FileTemplate.h"

#include <vector>
#include <string>

// #define H_SPACES() { GetOwningFile()->GetHeaderSpaces() }
// #define S_SPACES() { GetOwningFile()->GetSourceSpaces() }
// #define NEWLINE_TABBED() { std::endl << }

namespace ParserGenerator {

	class CodeSnippet_Base // Code Template
	{
	protected:
		/* Higher Priority is further up in the file */
		int m_Priority;
		std::vector<CodeSnippet_Base*> m_ChildSnippets;
		CodeSnippet_Base* m_ParentSnippet;
		FileTemplate* m_OwningFile;

		std::string m_InitialHeaderSpaces;
		std::string m_InitialSourceSpaces;

	public:
		CodeSnippet_Base(const int& InPriority, const std::vector<CodeSnippet_Base*> InChildSnippets);
		CodeSnippet_Base(const int& InPriority);
		virtual ~CodeSnippet_Base();

		const int& GetSnippetPriority() const { return m_Priority; }
		CodeSnippet_Base* GetParent() const { return m_ParentSnippet; }
		const std::vector<CodeSnippet_Base*>& GetChildren() const { return m_ChildSnippets; }
		FileTemplate* GetOwningFile() const;

		virtual void AttachSnippet(CodeSnippet_Base* InChild);
		virtual void SetParent(CodeSnippet_Base* InParent);
		virtual void SetOwningFile(FileTemplate* InFile);

		void AttachSnippet(const std::vector<CodeSnippet_Base*>& InChilden);

	public:
		void TriggerWrite();
		virtual void Write() const = 0;
		virtual void GenerateChildren() const;

	protected:
		const std::string& GetHeaderSpaces() const;
		const std::string& GetSourceSpaces() const;
	};
}