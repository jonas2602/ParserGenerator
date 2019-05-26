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
		virtual bool GetCodeFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream* OutHeaderStream, std::ofstream* OutSourceStream = nullptr) override;

		bool GetFileStream(const std::string& FileName, std::ofstream& OutFileStream, const std::string& RelativeDirectory = "", const std::string& FileType = ".txt") const;

	public:
		void GenerateFiles();
		void AddFileTemplate(const std::string& FileName, const std::string& DirectoryPath, const std::vector<CodeSnippet_Base*>& SnippetList);
	};

}