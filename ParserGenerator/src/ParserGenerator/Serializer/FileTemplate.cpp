#include "FileTemplate.h"
#include "Snippets/CodeSnippet.h"

#include <algorithm>
#include <fstream>


namespace ParserGenerator {

	FileTemplate::FileTemplate(const std::string& InFileName, const std::string& InDirectoryPath, IWriterInterface* InWriter, const std::vector<CodeSnippet_Base*> InRootSnippets)
		: m_FileName(InFileName), m_DirectoryPath(InDirectoryPath), m_Writer(InWriter), m_RootSnippets(InRootSnippets)
	{ }


	FileTemplate::~FileTemplate()
	{
	}

	void FileTemplate::AddSnippet(CodeSnippet_Base* SnippetInstance)
	{
		m_RootSnippets.push_back(SnippetInstance);
		SnippetInstance->SetOwningFile(this);
	}

	void FileTemplate::Write(IWriterInterface* Writer)
	{
		// Create File + Output Stream
		/*std::ofstream HeaderStream;
		std::ofstream SourceStream;
		Writer->GetCodeFileStreams(m_DirectoryPath, m_FileName, &HeaderStream, &SourceStream);

		AddDefaults(HeaderStream, SourceStream);*/

		// Sort Snippets by priority
		auto cmpLambda = [](CodeSnippet_Base* Left, CodeSnippet_Base* Right) {
			return Left->GetSnippetPriority() < Right->GetSnippetPriority();
		};
		std::sort(m_RootSnippets.begin(), m_RootSnippets.end(), cmpLambda);

		// Write Snippets to File
		for (CodeSnippet_Base* Snippet : m_RootSnippets)
		{
			//Snippet->Write(Writer, HeaderStream, SourceStream, nullptr);
			Snippet->Write();
		}
	}

	std::ofstream& FileTemplate::GetHeaderStream()
	{
		if (!m_HeaderStream.is_open())
		{
			m_Writer->GetFileStream(m_FileName, m_HeaderStream, m_DirectoryPath, ".h");
			m_HeaderStream << "// Automatically generated File" << std::endl
				<< "#pragma once" << std::endl
				<< std::endl;
		}

		return m_HeaderStream;
	}

	std::ofstream& FileTemplate::GetSourceStream()
	{
		if (!m_SourceStream.is_open())
		{
			m_Writer->GetFileStream(m_FileName, m_SourceStream, m_DirectoryPath, ".cpp");
			m_SourceStream << "// Automatically generated File" << std::endl
				<< "#include \"" << m_FileName << ".h\"" << std::endl
				<< std::endl;

		}

		return m_SourceStream;
	}

	std::ofstream& FileTemplate::GetTextStream()
	{
		if (!m_TextStream.is_open())
		{
			m_Writer->GetFileStream(m_FileName, m_TextStream, m_DirectoryPath, ".txt");
			m_TextStream << "// Automatically generated File" << std::endl
				<< std::endl;
		}

		return m_TextStream;
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