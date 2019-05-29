#include <iostream>
#include <fstream>
#include <sstream>
#include <Parser.h>

#include "gen/GenLexer.h"
#include "gen/GenParser.h"
#include "ExpressionVisitor.h"

int main()
{
	std::cout << "Start Calculator" << std::endl;

	std::ifstream File("src/calc.g");
	std::stringstream buffer;
	buffer << File.rdbuf();
	//std::cout << "Grammar:" << std::endl << buffer.str() << std::endl << std::endl;


	//PG::App::Generate(buffer.str());
	GenLexer Lexer = GenLexer("test123");
	std::vector<ParserGenerator::Token*> TokenStream = Lexer.GetTokenStream();
	//std::cout << TokenStream << std::endl << std::endl;

	GenParser Parser = GenParser(TokenStream);
	Rule_rulelist* root;
	Parser.Rulelist(root);

	ExpressionVisitor Visitor = ExpressionVisitor();
	float Result = Visitor.Visit(root);

	std::cin.get();
	return 0;
}

// Regex to ignore multiline comments /* */
// /\*+(?:[^/*][^*]*\*+)*/
// ISSUE: Detects /*/ as comment

// ORIGINAL: /\*+[^*]*\*+(?:[^/*][^*]*\*+)*/
// ISSUE: Detects /**/ not as comment

// Finding Quotes: "awdwd" 
// "[^"\\]*(?:\\.[^"\\]*)*"
// ATTENTION: Not Linebreak sensitive
// Sensitive Version: "[^"\\\n]*(\\.[^"\\\n]*)*"

// Finding Brackets: [abc\]]
// \[[^\]\\]*(?:\\.[^\]\\]*)*\]
