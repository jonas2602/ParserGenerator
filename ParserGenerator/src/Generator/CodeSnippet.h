#pragma once

#include "WriterInterface.h"
#include <fstream>
#include <vector>

class CodeSnippet_Base // Code Template
{
protected:
	/* Higher Priority is further up in the file */
	int m_Priority;
	std::vector<CodeSnippet_Base*> m_ChildSnippets;

public:
	CodeSnippet_Base(const int& InPriority = 0, const std::vector<CodeSnippet_Base*> InChildSnippets = {});
	~CodeSnippet_Base();

	const int& GetSnippetPriority() const { return m_Priority; }

public:
	virtual void Write(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream, const CodeSnippet_Base* ParentSnippet) const = 0;
	void GenerateChildren(IWriterInterface* Writer, std::ofstream& HeaderStream, std::ofstream& SourceStream) const;
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

