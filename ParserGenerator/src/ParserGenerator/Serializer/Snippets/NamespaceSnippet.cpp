#include "NamespaceSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_Namespace::Write() const
	{
		std::ofstream& HeaderStream = GetOwningFile()->GetHeaderStream();
		HeaderStream << std::endl;
		HeaderStream << m_InitialHeaderSpaces << "namespace " << m_NamespaceName << " {" << std::endl << std::endl;
		GetOwningFile()->PushHeaderTab();

		if (m_HeaderAndSource)
		{
			std::ofstream& SourceStream = GetOwningFile()->GetSourceStream();
			SourceStream << std::endl;
			SourceStream << m_InitialSourceSpaces << "namespace " << m_NamespaceName << " {" << std::endl;
			GetOwningFile()->PushSourceTab();
		}

		GenerateChildren();

		GetOwningFile()->PopHeaderTab();
		HeaderStream << m_InitialHeaderSpaces << "}" << std::endl;

		if (m_HeaderAndSource)
		{
			std::ofstream& SourceStream = GetOwningFile()->GetSourceStream();
			GetOwningFile()->PopSourceTab();
			SourceStream << m_InitialSourceSpaces << "}" << std::endl;
		}
	}

}