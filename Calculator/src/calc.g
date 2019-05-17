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