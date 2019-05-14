#include "CodeGenerator.h"
#include <filesystem>


namespace ParserGenerator {

	CodeGenerator::CodeGenerator(const std::string& InRootPath)
		: m_RootPath(InRootPath)
	{
	}


	CodeGenerator::~CodeGenerator()
	{
	}

	void CodeGenerator::GenerateFiles()
	{
		// Create empty files/folder structure
		// empty files if already existing
		// Add include Statements
		// Add namespace
		// iterate over snippets ordered by priority

		for (const std::pair<std::string, FileTemplate*>& Template : m_TemplateMap)
		{
			Template.second->Write(this);
		}
	}

	void CodeGenerator::AddFileTemplate(const std::string& FileName, const std::string& DirectoryPath, const std::vector<CodeSnippet_Base*>& SnippetList)
	{
		FileTemplate* NewFile = new FileTemplate(FileName, DirectoryPath, SnippetList);
		m_TemplateMap[FileName] = NewFile;
	}

	void CodeGenerator::GetFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream& OutHeaderStream, std::ofstream& OutSourceStream)
	{
		namespace fs = std::experimental::filesystem;

		// Create Directory if it doesn't exist
		fs::path DirPath = fs::path(m_RootPath) / fs::path(RelativeDirectory);
		fs::create_directories(DirPath);

		// Create Output Streams (creates or empties if already existing)
		OutHeaderStream.open(DirPath / fs::path(FileName + ".h"));
		OutSourceStream.open(DirPath / fs::path(FileName + ".cpp"));
	}

}