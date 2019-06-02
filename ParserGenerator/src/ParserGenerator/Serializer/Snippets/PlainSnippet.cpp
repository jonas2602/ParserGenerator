#include "PlainSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_Plain::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetTextStream();
		HeaderStream << m_TextStream.str();
	}

}