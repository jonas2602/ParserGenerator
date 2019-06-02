#pragma once

#include "CodeSnippet.h"

namespace ParserGenerator {

	class CodeSnippet_Include : public CodeSnippet_Base
	{
	protected:
		std::string m_Path;
		int m_bIntern;
		bool m_bHeader;

	public:
		CodeSnippet_Include(const std::string& InPath, const bool& InIntern = true, const bool& InHeader = true)
			: CodeSnippet_Base(0), m_Path(InPath), m_bIntern(InIntern), m_bHeader(InHeader)
		{ }

		virtual void Write() const override;
	};

}