rulelist: (parserrule | lexerrule) rulelist | ;

parserrule: PARSERID COLON parseror SEMICOLON;
parseror: parserlist | parserlist PIPE parseror;
parserlist: parserconst | parserconst parserlist;
parserconst: LEXERID | PARSERID | LITERAL | LP parseror RP;

lexerrule: LEXERID COLON regex action SEMICOLON;
action: ARROW PARSERID | ;
regex: (operator PIPE regex | operator) regex | ;
operator: anytime | once | optional | lexerconst;
anytime: lexerconst STAR;
once: lexerconst PLUS;
optional: lexerconst QUESTIONMARK;
lexerconst: LP regex RP | range | LEXERID | DOT | CHARSET | LITERAL;
range: LITERAL '..' LITERAL;

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

WS: [ \n]+ -> skip;