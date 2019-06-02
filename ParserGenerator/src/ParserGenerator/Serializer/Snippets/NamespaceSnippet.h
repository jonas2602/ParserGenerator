#pragma once

#include "CodeSnippet.h"

namespace ParserGenerator {

	class CodeSnippet_Namespace : public CodeSnippet_Base
	{
	protected:
		std::string m_NamespaceName;
		bool m_HeaderAndSource;

	public:
		CodeSnippet_Namespace(const std::string& InNamespaceName, bool InHeaderAndSource = true)
			: CodeSnippet_Base(1), m_NamespaceName(InNamespaceName), m_HeaderAndSource(InHeaderAndSource)
		{ }

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;

	};

}