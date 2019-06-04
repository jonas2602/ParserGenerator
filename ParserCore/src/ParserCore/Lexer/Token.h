#pragma once

#include <string>
#include <ostream>

#include "../Core.h"

namespace ParserCore {

	class Token
	{
	public:
		// End Of Stream Token Type
		static Token* EOS_TOKEN;

	protected:
		std::string m_Data;
		int m_Type;

		int m_StartLine;
		int m_StartColumn;
		int m_EndLine;
		int m_EndColumn;

	public:
		Token::Token(const std::string& InData, int InType, int InStartLine, int InStartColumn, int InEndLine, int InEndColumn)
			: m_Data(InData), m_Type(InType), m_StartLine(InStartLine), m_StartColumn(InStartColumn), m_EndLine(InEndLine), m_EndColumn(InEndColumn)
		{ }


		const std::string& GetTokenData() const { return m_Data; }
		int GetTokenType() const { return m_Type; }
		int GetStartLine() const { return m_StartLine; }
		int GetStartColumn() const { return m_StartColumn; }
		int GetEndLine() const { return m_EndLine; }
		int GetEndColumn() const { return m_EndColumn; }

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