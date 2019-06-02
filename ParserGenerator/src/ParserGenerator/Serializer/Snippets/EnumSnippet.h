#pragma once

#include "CodeSnippet.h"
#include <map>

namespace ParserGenerator {

	class CodeSnippet_Enum : public CodeSnippet_Base
	{
	protected:
		std::string m_EnumName;
		std::map<int, std::string> m_Entries;

	public:
		CodeSnippet_Enum(const std::string& InEnumName, const std::map<std::string, int>& InEnumEntries);

		void AddPair(const std::string& InKey, int InValue);

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;
	};

}