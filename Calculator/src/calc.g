expression: additive EOS;

additive: multiplicative | sum | subtract;
sum: multiplicative PLUS additive;
subtract : multiplicative MINUS additive;

multiplicative: constant | product | divide;
product: constant STAR multiplicative;
divide : constant SLASH multiplicative;

constant: FLOAT
		| INTEGER
        | LP additive RP;


// sum1: product1 sum2;
// sum2: '+' product1 sum2
//     | /** EPSILON */
//     ;
// 
// product1: constant1 product2;
// product2: '*' constant1 product2
//         | /** EPSILON */
//         ;
// 
// constant1: '(' sum1 ')'
//          | NUMBER
//          ;*

STAR: '*';
PLUS: '+';
MINUS: '-';
SLASH: '/';
LP: '(';
RP: ')';
// NUMBER: FLOAT | INTEGER;
FLOAT: [0-9]+ ('.' [0-9]+)?;
INTEGER: [0-9]+;


WS: [ \n\t\r]+ -> skip;