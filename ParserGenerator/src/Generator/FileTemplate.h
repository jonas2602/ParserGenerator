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

		std::ofstream m_HeaderStream;
		std::ofstream m_SourceStream;
		std::ofstream m_TextStream;

		std::string m_HeaderSpaces;
		std::string m_SourceSpaces;

		IWriterInterface* m_Writer;

	public:
		FileTemplate(const std::string& InFileName, const std::string& InDirectoryPath, IWriterInterface* InWriter, const std::vector<CodeSnippet_Base*> InRootSnippets = {});
		~FileTemplate();

		const std::string& GetFileName() const { return m_FileName; }
		const std::string& GetDirectoryPath() const { return m_DirectoryPath; }

	public:
		void AddSnippet(CodeSnippet_Base* SnippetInstance);
		void Write(IWriterInterface* Writer);

		std::ofstream& GetHeaderStream();
		std::ofstream& GetSourceStream();
		std::ofstream& GetTextStream();

		void PushHeaderTab() { m_HeaderSpaces.push_back('\t'); }
		void PopHeaderTab() { m_HeaderSpaces.pop_back(); }
		void PushSourceTab() { m_SourceSpaces.push_back('\t'); }
		void PopSourceTab() { m_SourceSpaces.pop_back(); }

		const std::string& GetHeaderSpaces() const { return m_HeaderSpaces; }
		const std::string& GetSourceSpaces() const { return m_SourceSpaces; }

	protected:
		void AddDefaults(std::ofstream& HeaderStream, std::ofstream& SourceStream);
	};

}