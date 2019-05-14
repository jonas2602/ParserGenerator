#pragma once

#include <vector>
#include <string>
#include "CodeSnippet.h"
#include "WriterInterface.h"

namespace ParserGenerator {

	class FileTemplate
	{
	protected:
		std::string m_FileName;
		std::string m_DirectoryPath;
		std::vector<CodeSnippet_Base*> m_RootSnippets;

	public:
		FileTemplate(const std::string& InFileName, const std::string& InDirectoryPath, const std::vector<CodeSnippet_Base*> InRootSnippets);
		~FileTemplate();

		const std::string& GetFileName() const { return m_FileName; }
		const std::string& GetDirectoryPath() const { return m_DirectoryPath; }

	public:
		void AddSnippet(CodeSnippet_Base* SnippetInstance);
		void Write(IWriterInterface* Writer);

	protected:
		void AddDefaults(std::ofstream& HeaderStream, std::ofstream& SourceStream);
	};

}