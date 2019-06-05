expression: additive EOS;

// additive: multiplicative | sum | subtract;
// sum: multiplicative PLUS additive;
// subtract : multiplicative MINUS additive;
// 
// multiplicative: constant | product | divide;
// product: constant STAR multiplicative;
// divide : constant SLASH multiplicative;
// 
// constant: FLOAT
// 		| INTEGER
//         | LP additive RP;

additive: multiplicative additive2;
additive2: PLUS multiplicative additive2
		 | MINUS multiplicative additive2
		 | /** EPSILON */
		 ;

multiplicative: constant multiplicative2;
multiplicative2: STAR constant multiplicative2
			   | SLASH constant multiplicative2
			   | /** EPSILON */
			   ;

constant: LP additive RP
        | NUMBER
        ;



//sum1: product1 sum2;
//sum2: '+' product1 sum2
//    | /** EPSILON */
//    ;
//
//product1: constant1 product2;
//product2: '*' constant1 product2
//        | /** EPSILON */
//        ;
//
//constant1: '(' sum1 ')'
//         | NUMBER
//         ;

STAR: '*';
PLUS: '+';
MINUS: '-';
SLASH: '/';
LP: '(';
RP: ')';
NUMBER: [0-9]+ ('.' [0-9]+)?;

WS: [ \n\t\r]+ -> skip;