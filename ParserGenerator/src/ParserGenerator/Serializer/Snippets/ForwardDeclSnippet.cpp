#include "ForwardDeclSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_ForwardDecl::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << m_Type << " " << m_Name << ";" << std::endl;
	}

}

