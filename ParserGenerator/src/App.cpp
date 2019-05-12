#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <sstream> 
#include <functional>
#include <ostream>
#include <list>

#include "Lexer/Lexer.h"
#include "Lexer/RegExp.h"
#include "Parser/ParserConfig.h"
#include "Parser/Parser.h"
#include "Parser/Visitor.h"
#include "Generator/CodeGenerator.h"

template<typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T*>& v) {
	std::transform(v.begin(), v.end(),
		std::ostream_iterator<T>(os, " "),
		[](T const* ptr) -> T const& { return *ptr; }
	);
	return os;
}


int main()
{
	std::cout << "Start" << std::endl;

	CodeGenerator Generator("gen");
	Generator.AddFileTemplate("test", "dir", {
		new CodeSnippet_Class("TestClass",{
			new CodeSnippet_Function("TestFunction",{
				"const std::string& TestParam",
				"MyClass*& OutParam"
			},{
				"return 0;"
			})
		}),
		new CodeSnippet_Include("ParentClass.h")
	});
	Generator.GenerateFiles();

	// Priority drops from high to low
	LexerConfig LexConfig;
	//LexConfig.Add("COMMENT", new RegExp(RegExp::AND({ RegExp::AND('/', '*'), RegExp::STAR(RegExp::ANY()), RegExp::AND('*', '/') })), ELexerAction::SKIP);	// /* .* */
	LexConfig.Add("PLUS", new RegExp(RegExp::CONST('+')));																									// +
	LexConfig.Add("TIMES", new RegExp(RegExp::CONST('*')));																									// *	
	LexConfig.Add("LEFTBRACKET", new RegExp(RegExp::CONST('(')));																							// (
	LexConfig.Add("RIGHTBRACKET", new RegExp(RegExp::CONST(')')));																							// )
	LexConfig.Add("NUM", new RegExp(RegExp::PLUS(RegExp::RANGE('0', '9'))));																				// [0-9]+
	//LexConfig.Add("Word", new RegExp(RegExp::PLUS(RegExp::OR(RegExp::RANGE('a', 'z'), RegExp::RANGE('A', 'Z')))));										// [a-zA-Z]+
	LexConfig.Add("WS", new RegExp(RegExp::PLUS(RegExp::OR({ ' ', RegExp::TAB, RegExp::CR, RegExp::LF }))), ELexerAction::SKIP);							// [ \t\r\n]+
	Lexer lex = Lexer(&LexConfig);

	std::string SourceCode = " 123  + 123";
	std::cout << "Input of \"" << SourceCode << "\" results in:" << std::endl;

	std::vector<Token*> TokenList = lex.Tokenize(SourceCode);
	std::cout << TokenList << std::endl;

	/*ParserConfig ParsConfig("S");
	ParsConfig.AddProduction("S", { "A" });

	ParsConfig.AddProduction("A", { "M", "PLUS", "A" });
	ParsConfig.AddProduction("A", { "M" });

	ParsConfig.AddProduction("A", { "M", "A'" });
	ParsConfig.AddProduction("A'", { "PLUS", "A" });
	ParsConfig.AddProduction("A'", { StateMachine::EPSILON_S });


	ParsConfig.AddProduction("M", { "F", "TIMES", "M" });
	ParsConfig.AddProduction("M", { "F" });

	ParsConfig.AddProduction("F", { "NUM" });
	ParsConfig.AddProduction("F", { "LEFTBRACKET", "A", "RIGHTBRACKET" });*/

	ParserConfig ParsConfig("S");
	ParsConfig.AddProduction("S", { "E" });

	ParsConfig.AddProduction("E", { "E", "PLUS", "T" });
	ParsConfig.AddProduction("E", { "T" });

	ParsConfig.AddProduction("T", { "T", "TIMES", "F" });
	ParsConfig.AddProduction("T", { "F" });

	ParsConfig.AddProduction("F", { "NUM" });
	ParsConfig.AddProduction("F", { "LEFTBRACKET", "E", "RIGHTBRACKET" });

	Parser pars(&ParsConfig);
	ParseTree* Tree = pars.BuildTree(TokenList);

	Visitor vis = Visitor();
	vis.AddFunctionPointer();
	vis.Visit(Tree->GetRootNode());
	
	/*
	float Result = Visitor().Visit(Tree->GetRootNode());
	std::cout << "Result: " << Result << std::endl;
*/
	std::cin.get();

	delete Tree;
	//delete vis;

	return 0;
}






