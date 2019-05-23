#include "Token.h"


namespace ParserGenerator {

	const std::string Token::EOS = "EOS";
	Token* Token::EOS_TOKEN = new Token("\0", -1, -1, -1);

	Token::Token(const std::string& InData, int InType, int InLineNumber, int InColumnNumber)
		: m_Data(InData), m_Type(InType), m_LineNumber(InLineNumber), m_ColumnNumber(InColumnNumber)
	{

	}


	Token::~Token()
	{

	}

}