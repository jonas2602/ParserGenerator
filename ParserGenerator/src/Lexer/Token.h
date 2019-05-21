#pragma once

#include <string>
#include <ostream>

namespace ParserGenerator {

	class Token
	{
	public:
		// End Of Stream Token Type
		static const std::string EOS;
		static Token* EOS_TOKEN;

	protected:
		std::string m_Data;
		std::string m_Name;
		int m_Type;

		int m_LineNumber;
		int m_ColumnNumber;

	public:
		Token(const std::string& InData, const std::string& InName, int InType, int InLineNumber, int InColumnNumber);
		~Token();


		const std::string& GetTokenData() const { return m_Data; }
		int GetTokenType() const { return m_Type; }
		const std::string& GetTokenName() const { return m_Name; }
		int GetLineNumber() const { return m_LineNumber; }
		int GetColumnNumber() const { return m_ColumnNumber; }

		friend std::ostream& operator<<(std::ostream& os, const Token& InToken)
		{
			// write obj to stream
			return os << "[\"" << InToken.m_Data << "\" (" << InToken.m_Type << ")]";
		}

		friend std::ostream& operator<<(std::ostream& os, const Token* InToken)
		{
			// write obj to stream
			return os << "[\"" << InToken->m_Data << "\" (" << InToken->m_Type << ")]";
		}
	};

}