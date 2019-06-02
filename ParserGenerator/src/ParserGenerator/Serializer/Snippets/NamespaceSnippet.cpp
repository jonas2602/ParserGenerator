#include "NamespaceSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_Namespace::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << std::endl;
		HeaderStream << m_InitialHeaderSpaces << "namespace " << m_NamespaceName << " {" << std::endl;
		m_OwningFile->PushHeaderTab();

		if (m_HeaderAndSource)
		{
			std::ofstream& SourceStream = m_OwningFile->GetSourceStream();
			SourceStream << std::endl;
			SourceStream << m_InitialSourceSpaces << "namespace " << m_NamespaceName << " {" << std::endl;
			m_OwningFile->PushSourceTab();
		}

		GenerateChildren();

		m_OwningFile->PopHeaderTab();
		HeaderStream << m_InitialHeaderSpaces << "}" << std::endl;

		if (m_HeaderAndSource)
		{
			std::ofstream& SourceStream = m_OwningFile->GetSourceStream();
			m_OwningFile->PopSourceTab();
			SourceStream << m_InitialSourceSpaces << "}" << std::endl;
		}
	}

}