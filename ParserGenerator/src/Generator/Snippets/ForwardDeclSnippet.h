#pragma once

#include "../CodeSnippet.h"
#include <string>

namespace ParserGenerator {

	class CodeSnippet_ForwardDecl : public CodeSnippet_Base
	{
	protected:
		std::string m_Type;
		std::string m_Name;

	public:
		CodeSnippet_ForwardDecl(const std::string& InType, const std::string& InName)
			: CodeSnippet_Base(1), m_Type(InType), m_Name(InName)
		{ }

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
	};

}