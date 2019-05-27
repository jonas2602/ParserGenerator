#pragma once

#include "WriterInterface.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


namespace ParserGenerator {
	class FileTemplate;

	class CodeSnippet_Base // Code Template
	{
	protected:
		/* Higher Priority is further up in the file */
		int m_Priority;
		std::vector<CodeSnippet_Base*> m_ChildSnippets;
		CodeSnippet_Base* m_ParentSnippet;
		FileTemplate* m_OwningFile;

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
		virtual void Write() const = 0;
		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const = 0;
		virtual void GenerateChildren(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream) const;
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
		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const override {};
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

		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const override;
	};

	class CodeSnippet_Parameter : public CodeSnippet_Base
	{

	};

	class CodeSnippet_Class : public CodeSnippet_Base
	{
	protected:
		std::string m_ClassName;
		std::string m_ParentName;

	public:
		CodeSnippet_Class(const std::string& InClassName, const std::vector<CodeSnippet_Base*>& InChildSnippets, const std::string& InParentName = "")
			: CodeSnippet_Base(1, InChildSnippets), m_ClassName(InClassName), m_ParentName(InParentName)
		{ }

		const std::string& GetClassName() const { return m_ClassName; }

		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const override;
	};

	class CodeSnippet_Function : public CodeSnippet_Base
	{
	protected:
		std::string m_FunctionName;
		std::vector<std::string> m_FunctionBody;
		std::vector<std::string> m_FunctionParameters;
		//CodeSnippet_Parameter* m_ReturnParameter;
		std::string m_ReturnType;

		bool m_bHeaderDefinition;
		bool m_bStatic;
		bool m_bConstant;
		bool m_bInline;

	public:
		CodeSnippet_Function(const std::string& InFunctionName, const std::vector<std::string>& InFunctionParameters, const std::vector<std::string>& InFunctionBody, const std::string& InReturnType = "void", const bool& InConstant = false, const bool& InStatic = false, const bool& InInline = false, const bool& InHeaderDefinition = false)
			: CodeSnippet_Base(0), m_FunctionName(InFunctionName), m_FunctionParameters(InFunctionParameters), m_FunctionBody(InFunctionBody), m_ReturnType(InReturnType), m_bConstant(InConstant), m_bStatic(InStatic), m_bInline(InInline), m_bHeaderDefinition(InHeaderDefinition)
		{ }

		/*~CodeSnippet_Function()
		{
			delete m_ReturnParameter;
		}*/

		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const override;

	};

	class CodeSnippet_Enum : public CodeSnippet_Base
	{
	protected:
		std::string m_EnumName;
		std::map<int, std::string> m_Entries;

	public:
		CodeSnippet_Enum(const std::string& InEnumName, const std::map<std::string, int>& InEnumEntries);

		virtual void Write() const override;
		virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const override;
	};

}