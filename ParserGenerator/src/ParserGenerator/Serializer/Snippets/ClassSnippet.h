#pragma once

#include "CodeSnippet.h"

namespace ParserGenerator {

	class CodeSnippet_Class : public CodeSnippet_Base
	{
	protected:
		std::string m_ClassName;
		std::string m_ParentName;
		bool m_bTemplate;
		std::vector<std::string> m_TypeNames;

		std::vector<std::pair<std::string, std::vector<CodeSnippet_Base*>>> m_PrivacyGroups;

	public:
		CodeSnippet_Class(const std::string& InClassName, const std::string& InParentName = "");

		const std::string& GetClassName() const { return m_ClassName; }

		virtual void AttachSnippet(CodeSnippet_Base* InChild) override;
		void CreateNewGroup(const std::string& InPrivacy);
		void AddTemplating(const std::vector<std::string>& InTypeNames);

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
		virtual void GenerateChildren() const override;
	};

}