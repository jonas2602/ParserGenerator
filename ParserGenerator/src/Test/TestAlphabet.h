#pragma once

#include <string>

//namespace Alphabet {

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
	ANYTIME = 1,
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
	PARSEROR = 12,
	PARSEROR2 = 13,
	PARSERRULE = 14,
	REGEX = 15,
	RULELIST = 16,
};

/*std::string GetRuleName(ERuleType Rule)
{
	switch (Rule)
	{
		case ACTION: return "ACTION";
		case ANYTIME: return "ANYTIME";
		case LEXERCONST: return "LEXERCONST";
		case LEXEROR: return "LEXEROR";
		case LEXEROR2: return "LEXEROR2";
		case LEXERRULE: return "LEXERRULE";
		case ONCE: return "ONCE";
		case OPERATOR: return "OPERATOR";
		case OPERATOR2: return "OPERATOR2";
		case OPTIONAL: return "OPTIONAL";
		case PARSERCONST: return "PARSERCONST";
		case PARSERLIST: return "PARSERLIST";
		case PARSERLIST2: return "PARSERLIST2";
		case PARSEROR: return "PARSEROR";
		case PARSEROR2: return "PARSEROR2";
		case PARSERRULE: return "PARSERRULE";
		case REGEX: return "REGEX";
		case RULELIST: return "RULELIST";
		default: return "UNKNOWN";
	}
}

std::string GetTokenName(ETokenType Token)
{
	switch (Token)
	{
		case WS: return "WS";
		case BLOCKCOMMENT: return "BLOCKCOMMENT";
		case LINECOMMENT: return "LINECOMMENT";
		case LEXERID: return "LEXERID";
		case ARROW: return "ARROW";
		case QUESTIONMARK: return "QUESTIONMARK";
		case CHARSET: return "CHARSET";
		case STAR: return "STAR";
		case PLUS: return "PLUS";
		case DOT: return "DOT";
		case LITERAL: return "LITERAL";
		case PARSERID: return "PARSERID";
		case SEMICOLON: return "SEMICOLON";
		case COLON: return "COLON";
		case PIPE: return "PIPE";
		case RIGHTPARENTHESE: return "RIGHTPARENTHESE";
		case LEFTPARENTHESE: return "LEFTPARENTHESE";
		default: return "UNKNOWN";
	}
}*/

//std::ostream& operator<<(std::ostream& os, const ETokenType& c)
//{
//	switch (c)
//	{
//	case WS: os << "WS"; break;
//	case BLOCKCOMMENT: os << "BLOCKCOMMENT"; break;
//	case LINECOMMENT: os << "LINECOMMENT"; break;
//	case LEXERID: os << "LEXERID"; break;
//	case ARROW: os << "ARROW"; break;
//	case QUESTIONMARK: os << "QUESTIONMARK"; break;
//	case CHARSET: os << "CHARSET"; break;
//	case STAR: os << "STAR"; break;
//	case PLUS: os << "PLUS"; break;
//	case DOT: os << "DOT"; break;
//	case LITERAL: os << "LITERAL"; break;
//	case PARSERID: os << "PARSERID"; break;
//	case SEMICOLON: os << "SEMICOLON"; break;
//	case COLON: os << "COLON"; break;
//	case PIPE: os << "PIPE"; break;
//	case RIGHTPARENTHESE: os << "RIGHTPARENTHESE"; break;
//	case LEFTPARENTHESE: os << "LEFTPARENTHESE"; break;
//	default: os.setstate(std::ios_base::failbit);
//	}
//	return os;
//}

//}
