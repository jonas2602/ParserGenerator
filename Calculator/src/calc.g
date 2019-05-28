rulelist: (parserrule | lexerrule) rulelist | ;

parserrule: PARSERID COLON parseror SEMICOLON;
// parseror: parserlist | parserlist PIPE parseror;
parseror: parserlist parseror2;
parseror2: PIPE parserlist parseror2 | ;
// parserlist: parserconst | parserconst parserlist;
parserlist: parserconst parserlist | ;
parserconst: LEXERID | PARSERID | LITERAL | LP parseror RP;


lexerrule: LEXERID COLON regex action SEMICOLON;
action: ARROW PARSERID | ;
// regex: (operator PIPE regex | operator) regex | ;
regex: lexeror regex | ;
lexeror: operator lexeror2;
lexeror2: PIPE operator lexeror2 | ;
// operator: anytime | once | optional | lexerconst;
operator: lexerconst operator2;
operator2: STAR | PLUS | QUESTIONMARK | ;
// anytime: lexerconst STAR;
// once: lexerconst PLUS;
// optional: lexerconst QUESTIONMARK;
// lexerconst: LP regex RP | range | LEXERID | DOT | CHARSET | LITERAL;
lexerconst: LP regex RP | LEXERID | DOT | CHARSET | LITERAL;
// range: LITERAL '..' LITERAL;

LP: '(';
RP: ')';
PIPE: '|';
COLON: ':';
SEMICOLON: ';';
PARSERID: [a-z][a-zA-Z0-9_]*;
LITERAL: '\''~['\\]*('\\'.~['\\]*)*'\'';

DOT: '.';
PLUS: '+';
STAR: '*';
CHARSET: '~'?'['~[\]\\]*('\\'.~[\]\\]*)*']';
QUESTIONMARK: '?';
ARROW: '->';
LEXERID: [A-Z][a-zA-Z0-9_]*;

WS: [ \n\t\r]+ -> skip;