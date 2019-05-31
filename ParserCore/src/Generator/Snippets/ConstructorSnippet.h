#pragma once

#include "../CodeSnippet.h"

namespace ParserGenerator {

	class CodeSnippet_Constructor : public CodeSnippet_Base
	{
	protected:
		std::vector<std::string> m_ConstructorBody;
		std::vector<std::string> m_ConstructorParameters;
		std::map<std::string, std::string> m_PreConstructorCalls;
		bool m_bHeaderDefinition;

	public:
		CodeSnippet_Constructor(const std::vector<std::string>& InConstructorBody, const std::vector<std::string>& InConstructorParameters, const std::map<std::string, std::string>& InPreConstructorCalls, bool InHeaderDefinition = false)
			: CodeSnippet_Base(0), m_ConstructorBody(InConstructorBody), m_ConstructorParameters(InConstructorParameters), m_PreConstructorCalls(InPreConstructorCalls), m_bHeaderDefinition(InHeaderDefinition)
		{ }

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;

	protected:
		const std::string GetClassName() const;
		std::string CreateParameterString() const;
	};

}