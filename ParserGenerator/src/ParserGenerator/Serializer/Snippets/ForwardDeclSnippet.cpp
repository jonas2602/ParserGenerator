#include "ForwardDeclSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_ForwardDecl::Write() const
	{
		std::ofstream& HeaderStream = GetOwningFile()->GetHeaderStream();
		HeaderStream << m_InitialHeaderSpaces << m_Type << " " << m_Name << ";" << std::endl;
	}

}

