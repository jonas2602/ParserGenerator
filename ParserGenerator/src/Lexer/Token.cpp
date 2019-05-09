#include "Token.h"



Token::Token(const std::string& InData, std::string InType, int InPriority, int InLineNumber, int InColumnNumber)
	: m_Data(InData), m_Type(InType), m_Priority(InPriority), m_LineNumber(InLineNumber), m_ColumnNumber(InColumnNumber)
{
}


Token::~Token()
{
}
