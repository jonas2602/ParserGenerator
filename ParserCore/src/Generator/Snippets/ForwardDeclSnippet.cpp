#include "ForwardDeclSnippet.h"
#include "../FileTemplate.h"

namespace ParserCore {

	void CodeSnippet_ForwardDecl::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
		HeaderStream << m_Type << " " << m_Name << ";" << std::endl;
	}

}

