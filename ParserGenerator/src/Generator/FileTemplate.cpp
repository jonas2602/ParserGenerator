#include "FileTemplate.h"
#include <algorithm>
#include <fstream>


namespace ParserGenerator {

	FileTemplate::FileTemplate(const std::string& InFileName, const std::string& InDirectoryPath, const std::vector<CodeSnippet_Base*> InRootSnippets)
		: m_FileName(InFileName), m_DirectoryPath(InDirectoryPath), m_RootSnippets(InRootSnippets)
	{ }


	FileTemplate::~FileTemplate()
	{
	}

	void FileTemplate::AddSnippet(CodeSnippet_Base* SnippetInstance)
	{
		m_RootSnippets.push_back(SnippetInstance);
	}

	void FileTemplate::Write(IWriterInterface* Writer)
	{
		// Create File + Output Stream
		std::ofstream HeaderStream;
		std::ofstream SourceStream;
		Writer->GetFileStreams(m_DirectoryPath, m_FileName, HeaderStream, SourceStream);

		AddDefaults(HeaderStream, SourceStream);

		// Sort Snippets by priority
		auto cmpLambda = [](CodeSnippet_Base * Left, CodeSnippet_Base * Right) {
			return Left->GetSnippetPriority() < Right->GetSnippetPriority();
		};
		std::sort(m_RootSnippets.begin(), m_RootSnippets.end(), cmpLambda);

		// Write Snippets to File
		for (CodeSnippet_Base* Snippet : m_RootSnippets)
		{
			Snippet->Write(Writer, HeaderStream, SourceStream, nullptr);
		}
	}

	void FileTemplate::AddDefaults(std::ofstream& HeaderStream, std::ofstream& SourceStream)
	{
		HeaderStream << "// Automatically generated File" << std::endl
			<< std::endl
			<< "#pragma once" << std::endl
			<< std::endl;

		SourceStream << "// Automatically generated File" << std::endl
			<< std::endl;
	}

}