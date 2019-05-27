#pragma once

#include "FileTemplate.h"
#include "WriterInterface.h"
#include <vector>

namespace ParserGenerator {

	class VirtualFolder
	{

	};

	class CodeGenerator : public IWriterInterface
	{
	protected:
		// FileName -> Template
		std::vector<FileTemplate*> m_TemplateList;
		std::string m_RootPath;

	public:
		CodeGenerator(const std::string& RootPath);
		~CodeGenerator();

	public:
		// Inherited via IWriterInterface
		virtual bool GetCodeFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream* OutHeaderStream, std::ofstream* OutSourceStream = nullptr) override;
		virtual bool GetFileStream(const std::string& FileName, std::ofstream& OutFileStream, const std::string& RelativeDirectory = "", const std::string& FileType = ".txt") override;

	public:
		void GenerateFiles();
		void AddFileTemplate(const std::string& FileName, const std::string& DirectoryPath, const std::vector<CodeSnippet_Base*>& SnippetList);

		virtual FileTemplate* CreateVirtualFile(const std::string& FileName, const std::string& DirectoryPath);
	};

}