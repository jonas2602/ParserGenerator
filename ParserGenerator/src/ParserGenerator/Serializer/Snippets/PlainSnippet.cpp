#include "PlainSnippet.h"

namespace ParserGenerator {

	void CodeSnippet_Plain::Write() const
	{
		std::ofstream& FileStream = GetOwningFile()->GetTextStream();
		FileStream << m_TextStream.str() << std::endl;
		// endl is required because otehrwise it won't write for no reason
	}

}