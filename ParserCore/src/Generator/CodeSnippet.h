#pragma once

#include "WriterInterface.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

// #define H_SPACES() { m_OwningFile->GetHeaderSpaces() }
// #define S_SPACES() { m_OwningFile->GetSourceSpaces() }
// #define NEWLINE_TABBED() { std::endl << }

namespace ParserCore {
	class FileTemplate;

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
		~CodeSnippet_Base();

		const int& GetSnippetPriority() const { return m_Priority; }
		CodeSnippet_Base* GetParent() const { return m_ParentSnippet; }
		const std::vector<CodeSnippet_Base*>& GetChildren() const { return m_ChildSnippets; }
		FileTemplate* GetOwningFile() const { return m_OwningFile; }

		virtual void AttachSnippet(CodeSnippet_Base* InChild);
		virtual void SetParent(CodeSnippet_Base* InParent);
		virtual void SetOwningFile(FileTemplate* InFile);

	public:
		void TriggerWrite();
		virtual void Write() const = 0;
		virtual void GenerateChildren() const;

	protected:
		const std::string& GetHeaderSpaces() const;
		const std::string& GetSourceSpaces() const;
	};

	class CodeSnippet_Plain : public CodeSnippet_Base
	{
	protected:
		std::stringstream m_TextStream;

	public:
		CodeSnippet_Plain()
			: CodeSnippet_Base(1)
		{ }

		std::stringstream& GetTextStream() { return m_TextStream; }

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
	};

	class CodeSnippet_Include : public CodeSnippet_Base
	{
	protected:
		std::string m_Path;
		int m_bIntern;
		bool m_bHeader;

	public:
		CodeSnippet_Include(const std::string& InPath, const bool& InIntern = true, const bool& InHeader = true)
			: CodeSnippet_Base(0), m_Path(InPath), m_bIntern(InIntern), m_bHeader(InHeader)
		{ }

		virtual void Write() const override;
	};

	class CodeSnippet_Parameter : public CodeSnippet_Base
	{

	};

	class CodeSnippet_Enum : public CodeSnippet_Base
	{
	protected:
		std::string m_EnumName;
		std::map<int, std::string> m_Entries;

	public:
		CodeSnippet_Enum(const std::string& InEnumName, const std::map<std::string, int>& InEnumEntries);

		void AddPair(const std::string& InKey, int InValue);
			
	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
	};

}