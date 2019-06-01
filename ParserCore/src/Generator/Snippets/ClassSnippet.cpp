#include "ClassSnippet.h"
#include "ClassSnippet.h"
#include "../FileTemplate.h"

namespace ParserCore {

	CodeSnippet_Class::CodeSnippet_Class(const std::string& InClassName, const std::string& InParentName)
		: CodeSnippet_Base(2), m_ClassName(InClassName), m_ParentName(InParentName), m_bTemplate(false)
	{
		// Start with Private Group
		CreateNewGroup("private");
	}

	void CodeSnippet_Class::AttachSnippet(CodeSnippet_Base* InChild)
	{
		CodeSnippet_Base::AttachSnippet(InChild);

		// Add Snippet to ActiveGroup
		std::pair<std::string, std::vector<CodeSnippet_Base*>>& ActiveGroup = m_PrivacyGroups.back();
		ActiveGroup.second.push_back(InChild);
	}

	void CodeSnippet_Class::CreateNewGroup(const std::string& InPrivacy)
	{
		m_PrivacyGroups.push_back(std::pair<std::string, std::vector<CodeSnippet_Base*>>(InPrivacy, {}));
	}

	void CodeSnippet_Class::AddTemplating(const std::vector<std::string>& InTypeNames)
	{
		m_bTemplate = true;
		m_TypeNames = InTypeNames;
	}

	void CodeSnippet_Class::Write() const
	{
		std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();

		HeaderStream << std::endl;
		if (m_bTemplate)
		{
			HeaderStream << m_InitialHeaderSpaces << "template<";
			bool bFirst = true;
			for (const std::string& TypeName : m_TypeNames)
			{
				if (bFirst) {
					HeaderStream << "typename " << TypeName;
					bFirst = false;
				}
				else
				{
					HeaderStream << ", typename " << TypeName;
				}
			}
			HeaderStream << ">" << std::endl;
		}

		HeaderStream << m_InitialHeaderSpaces << "class " << m_ClassName;
		if (!m_ParentName.empty())
		{
			HeaderStream << ": public " << m_ParentName;
		}
		HeaderStream << std::endl;
		HeaderStream << m_InitialHeaderSpaces << "{" << std::endl;
		m_OwningFile->PushHeaderTab();
		GenerateChildren();
		m_OwningFile->PopHeaderTab();
		HeaderStream << m_InitialHeaderSpaces << "};" << std::endl;
	}

	void CodeSnippet_Class::GenerateChildren() const
	{
		for (const std::pair<std::string, std::vector<CodeSnippet_Base*>>& PrivacyGroup : m_PrivacyGroups)
		{
			// Ignore if empty
			if (PrivacyGroup.second.size() == 0) continue;

			// 
			std::ofstream& HeaderStream = m_OwningFile->GetHeaderStream();
			HeaderStream << PrivacyGroup.first << ":" << std::endl;

			// 
			for (CodeSnippet_Base* Child : PrivacyGroup.second)
			{
				Child->TriggerWrite();
			}

			HeaderStream << std::endl;
		}
	}

}