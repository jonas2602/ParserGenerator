#pragma once

#include "../CodeSnippet.h"

namespace ParserGenerator {

	class CodeSnippet_Switch : public CodeSnippet_Base
	{
	protected:
		std::string m_Statement;
		std::map<std::string, std::vector<std::string>> m_Cases;

	public:
		CodeSnippet_Switch(const std::string& InStatement, const std::map<std::string, std::vector<std::string>>& InCases = {})
			: CodeSnippet_Base(0), m_Statement(InStatement), m_Cases(InCases)
		{ }

		void AddCase(const std::string& InCondition, const std::vector<std::string>& InBody);

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;

		std::vector<std::string> GetRawLines() const;
	};

}