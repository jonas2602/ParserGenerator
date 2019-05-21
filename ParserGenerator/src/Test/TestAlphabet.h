#pragma once

#include <iostream>
#include <ostream>

namespace Alphabet {

	enum ETokenType {
		WS = 0,
		BLOCKCOMMENT = 1,
		LINECOMMENT = 2,
		LEXERID = 3,
		ARROW = 4,
		QUESTIONMARK = 5,
		CHARSET = 6,
		STAR = 7,
		PLUS = 8,
		DOT = 9,
		LITERAL = 10,
		PARSERID = 11,
		SEMICOLON = 12,
		COLON = 13,
		PIPE = 14,
		RIGHTPARENTHESE = 15,
		LEFTPARENTHESE = 16,
	};

	enum ERuleType {
		ACTION = 0,
		ANZTIME = 1,
		LEXERCONST = 2,
		LEXEROR = 3,
		LEXEROR2 = 4,
		LEXERRULE = 5,
		ONCE = 6,
		OPERATOR = 7,
		OPERATOR2 = 8,
		OPTIONAL = 9,
		PARSERCONST = 10,
		PARSERLIST = 11,
		PARSERLIST2 = 12,
		PARSEROR = 13,
		PARSEROR2 = 14,
		PARSERRULE = 15,
		REGEX = 16,
		RULELIST = 17,
	};

	std::ostream& operator<<(std::ostream& os, const ETokenType& c)
	{
		switch (c)
		{
		case WS: os << "WS"; break;
		case BLOCKCOMMENT: os << "BLOCKCOMMENT"; break;
		case LINECOMMENT: os << "LINECOMMENT"; break;
		case LEXERID: os << "LEXERID"; break;
		case ARROW: os << "ARROW"; break;
		case QUESTIONMARK: os << "QUESTIONMARK"; break;
		case CHARSET: os << "CHARSET"; break;
		case STAR: os << "STAR"; break;
		case PLUS: os << "PLUS"; break;
		case DOT: os << "DOT"; break;
		case LITERAL: os << "LITERAL"; break;
		case PARSERID: os << "PARSERID"; break;
		case SEMICOLON: os << "SEMICOLON"; break;
		case COLON: os << "COLON"; break;
		case PIPE: os << "PIPE"; break;
		case RIGHTPARENTHESE: os << "RIGHTPARENTHESE"; break;
		case LEFTPARENTHESE: os << "LEFTPARENTHESE"; break;
		default: os.setstate(std::ios_base::failbit);
		}
		return os;
	}

}
