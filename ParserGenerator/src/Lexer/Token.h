#pragma once

#include <string>
#include <ostream>

namespace ParserGenerator {

	class Token
	{
	protected:
		std::string m_Data;
		std::string m_Type;
		int m_Priority;

		int m_LineNumber;
		int m_ColumnNumber;

	public:
		Token(const std::string& InData, std::string InType, int InPriority, int InLineNumber, int InColumnNumber);
		~Token();

		const std::string& GetTokenData() const { return m_Data; }
		const std::string& GetTokenType() const { return m_Type; }
		int GetLineNumber() const { return m_LineNumber; }
		int GetColumnNumber() const { return m_ColumnNumber; }

		friend std::ostream& operator<<(std::ostream& os, const Token& InToken)
		{
			// write obj to stream
			return os << "[\"" << InToken.m_Data << "\" (" << InToken.m_Type << ")]";
		}
	};

}