// Automatically generated File
#pragma once

enum ETokenType { 
	EOS = -1, 
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
	RP = 15, 
	LP = 16, 
};

enum ERuleType { 
	ACTION = 0, 
	LEXERCONST = 1, 
	LEXEROR = 2, 
	LEXEROR2 = 3, 
	LEXERRULE = 4, 
	OPERATORR = 5, 
	OPERATORR2 = 6, 
	PARSERCONST = 7, 
	PARSERLIST = 8, 
	PARSEROR = 9, 
	PARSEROR2 = 10, 
	PARSERRULE = 11, 
	REGEX = 12, 
	RULELIST = 13, 
};

