#include "CodeGenerator.h"
#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace ParserCore {

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

		for (FileTemplate* Template : m_TemplateList)
		{
			Template->Write(this);
		}
	}

	void CodeGenerator::AddFileTemplate(const std::string& FileName, const std::string& DirectoryPath, const std::vector<CodeSnippet_Base*>& SnippetList)
	{
		FileTemplate* NewFile = new FileTemplate(FileName, DirectoryPath, this, SnippetList);
		m_TemplateList.push_back(NewFile);
	}

	FileTemplate* CodeGenerator::CreateVirtualFile(const std::string& FileName, const std::string& DirectoryPath)
	{
		FileTemplate* NewFile = new FileTemplate(FileName, DirectoryPath, this);
		m_TemplateList.push_back(NewFile);

		return NewFile;
	}

	bool CodeGenerator::GetCodeFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream* OutHeaderStream, std::ofstream* OutSourceStream)
	{
		//namespace fs = std::experimental::filesystem;

		// Create Directory if it doesn't exist
		fs::path DirPath = fs::path(m_RootPath) / fs::path(RelativeDirectory);
		fs::create_directories(DirPath);

		// Create Output Streams (creates or empties if already existing)
		if (OutHeaderStream) { OutHeaderStream->open(DirPath / fs::path(FileName + ".h")); }
		if (OutSourceStream) { OutSourceStream->open(DirPath / fs::path(FileName + ".cpp")); }

		return true;
	}

	bool CodeGenerator::GetFileStream(const std::string& FileName, std::ofstream& OutFileStream, const std::string& RelativeDirectory, const std::string& FileType)
	{
		// Create Directory if it doesn't exist
		fs::path DirPath = fs::path(m_RootPath) / fs::path(RelativeDirectory);
		fs::create_directories(DirPath);

		// Create Output Stream (creates or empties if already existing)
		OutFileStream.open(DirPath / fs::path(FileName + FileType));
		return true;
	}

}