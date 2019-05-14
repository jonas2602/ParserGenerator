#pragma once

#include "FileTemplate.h"
#include "WriterInterface.h"
#include <map>

namespace ParserGenerator {

	class VirtualFolder
	{

	};

	class CodeGenerator : public IWriterInterface
	{
	protected:
		// FileName -> Template
		std::map<std::string, FileTemplate*> m_TemplateMap;
		std::string m_RootPath;

	public:
		CodeGenerator(const std::string& RootPath);
		~CodeGenerator();

	public:
		// Inherited via IWriterInterface
		virtual void GetFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream& OutHeaderStream, std::ofstream& OutSourceStream) override;

	public:
		void GenerateFiles();
		void AddFileTemplate(const std::string& FileName, const std::string& DirectoryPath, const std::vector<CodeSnippet_Base*>& SnippetList);
	};

}