#include "ForwardDeclSnippet.h"
#include "../FileTemplate.h"

void ParserGenerator::CodeSnippet_ForwardDecl::Write() const
{
	std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
	HeaderStream << m_Type << " " << m_Name << ";" << std::endl;
}
