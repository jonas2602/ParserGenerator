#include "Token.h"


namespace ParserGenerator {

	const std::string Token::EOS = "EOS";
	Token* Token::EOS_TOKEN = new Token("\0", Token::EOS, -1, -1, -1);

	Token::Token(const std::string& InData, const std::string& InName, int InType, int InLineNumber, int InColumnNumber)
		: m_Data(InData), m_Name(InName), m_Type(InType), m_LineNumber(InLineNumber), m_ColumnNumber(InColumnNumber)
	{

	}


	Token::~Token()
	{

	}

}