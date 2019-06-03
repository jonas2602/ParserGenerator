#include "Token.h"
#include "../ParserTypes.h"


namespace ParserCore {

	Token* Token::EOS_TOKEN = new Token(EOS_S, EOS, -1, -1);

	Token::Token(const std::string& InData, int InType, int InLineNumber, int InColumnNumber)
		: m_Data(InData), m_Type(InType), m_LineNumber(InLineNumber), m_ColumnNumber(InColumnNumber)
	{

	}


	Token::~Token()
	{

	}

}