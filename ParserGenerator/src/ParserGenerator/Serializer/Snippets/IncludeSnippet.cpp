#include "IncludeSnippet.h"


namespace ParserGenerator {

	void CodeSnippet_Include::Write() const
	{
		std::ofstream& UsedFile = m_bHeader ? GetOwningFile()->GetHeaderStream() : GetOwningFile()->GetSourceStream();
		UsedFile << "#include ";
		UsedFile << (m_bIntern ? "\"" : "<");
		UsedFile << m_Path;
		UsedFile << (m_bIntern ? "\"" : ">");
		UsedFile << std::endl;
	}

}