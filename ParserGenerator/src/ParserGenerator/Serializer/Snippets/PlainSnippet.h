#pragma once

#include "CodeSnippet.h"
#include <sstream>

namespace ParserGenerator {

	class CodeSnippet_Plain : public CodeSnippet_Base
	{
	protected:
		std::stringstream m_TextStream;

	public:
		CodeSnippet_Plain()
			: CodeSnippet_Base(1)
		{ }

		std::stringstream& GetTextStream() { return m_TextStream; }

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
	};

}