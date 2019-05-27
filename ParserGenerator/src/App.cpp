#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
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
#include "Core.h"
#include "App.h"
#include "ParserTypes.h"

#include "Test/TestLexer.h"
#include "Test/TestParser.h"
#include "Test/TestVisitor.h"
#include "Builder/ParserBuilder.h"

namespace ParserGenerator {


	template<typename T>
	std::ostream& operator <<(std::ostream& os, const std::vector<T*>& v) {
		std::transform(v.begin(), v.end(),
			std::ostream_iterator<T>(os, " "),
			[](T const* ptr) -> T const& { return *ptr; }
		);
		return os;
	}



	int App::main()
	{
		std::cout << "Start Generator" << std::endl;

		//CodeGenerator Generator("gen");
		//Generator.AddFileTemplate("test", "dir", {
		//	new CodeSnippet_Class("TestClass",{
		//		new CodeSnippet_Function("TestFunction",{
		//			"const std::string& TestParam",
		//			"MyClass*& OutParam"
		//		},{
		//			"return 0;"
		//		})
		//	}),
		//	new CodeSnippet_Include("ParentClass.h")
		//	});
		//Generator.GenerateFiles();

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
		/*Lexer lex = Lexer(&LexConfig);

		std::string SourceCode = "123  + 123";
		std::cout << "Input of \"" << SourceCode << "\" results in:" << std::endl;

		std::vector<Token*> TokenList = lex.Tokenize(SourceCode);
		std::cout << TokenList << std::endl;*/

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

		ParserConfig ParsConfig = ParserConfig();
		ParsConfig.AddProduction("S", { "E" });

		ParsConfig.AddProduction("E", { "E", "PLUS", "T" });
		ParsConfig.AddProduction("E", { "T" });

		ParsConfig.AddProduction("T", { "T", "TIMES", "F" });
		ParsConfig.AddProduction("T", { "F" });

		ParsConfig.AddProduction("F", { "NUM" });
		ParsConfig.AddProduction("F", { "LEFTBRACKET", "E", "RIGHTBRACKET" });

		/*Parser pars(&ParsConfig);
		ParseTree* Tree = pars.BuildTree(TokenList);

		Visitor vis = Visitor();
		vis.AddFunctionPointer();
		vis.Visit((RuleNode*)Tree);*/

		/*
		float Result = Visitor().Visit(Tree->GetRootNode());
		std::cout << "Result: " << Result << std::endl;
	*/
		std::cin.get();

		//delete Tree;
		//delete vis;

		return 0;
	}


	void App::Generate(const std::string& SourceCode)
	{
		std::cout << "Start Generator" << std::endl;

		// Priority drops from high to low
		LexerConfig LexConfig;
		LexConfig.Add("LEFTPARENTHESE", new RegExp(RegExp::CONST('(')));
		LexConfig.Add("RIGHTPARENTHESE", new RegExp(RegExp::CONST(')')));
		LexConfig.Add("PIPE", new RegExp(RegExp::CONST('|')));
		LexConfig.Add("COLON", new RegExp(RegExp::CONST(':')));
		LexConfig.Add("SEMICOLON", new RegExp(RegExp::CONST(';')));
		LexConfig.Add("PARSERID", new RegExp(RegExp::AND(RegExp::RANGE('a', 'z'), RegExp::STAR(RegExp::LIST(std::vector<Node_CONST*>({ RegExp::RANGE('a', 'z'), RegExp::RANGE('A', 'Z'), RegExp::RANGE('0', '9'), RegExp::CONST('_') }))))));
		LexConfig.Add("LITERAL", new RegExp(RegExp::AND({ RegExp::CONST('\''), RegExp::STAR(RegExp::EXCEPT({ '\'', '\\' })),  RegExp::STAR(RegExp::AND({RegExp::CONST('\\'), RegExp::ANY(), RegExp::STAR(RegExp::EXCEPT({'\\', '\''}))})), RegExp::CONST('\'') })));

		LexConfig.Add("DOT", new RegExp(RegExp::CONST('.')));
		LexConfig.Add("PLUS", new RegExp(RegExp::CONST('+')));
		LexConfig.Add("STAR", new RegExp(RegExp::CONST('*')));
		LexConfig.Add("CHARSET", new RegExp(RegExp::AND({ RegExp::OPTIONAL('~') , RegExp::CONST('['), RegExp::STAR(RegExp::EXCEPT({ ']', '\\' })),  RegExp::STAR(RegExp::AND({RegExp::CONST('\\'), RegExp::ANY(), RegExp::STAR(RegExp::EXCEPT({'\\', ']'}))})), RegExp::CONST(']') })));
		LexConfig.Add("QUESTIONMARK", new RegExp(RegExp::CONST('?')));
		LexConfig.Add("ARROW", new RegExp(RegExp::SEQUENCE("->")));
		LexConfig.Add("LEXERID", new RegExp(RegExp::AND(RegExp::RANGE('A', 'Z'), RegExp::STAR(RegExp::LIST(std::vector<Node_CONST*>({ RegExp::RANGE('a', 'z'), RegExp::RANGE('A', 'Z'), RegExp::RANGE('0', '9'), RegExp::CONST('_') }))))));

		LexConfig.Add("LINECOMMENT", new RegExp(RegExp::AND(RegExp::SEQUENCE("//"), RegExp::STAR(RegExp::EXCEPT({ RegExp::LF })))), ELexerAction::SKIP);
		LexConfig.Add("BLOCKCOMMENT", new RegExp(RegExp::AND({ RegExp::CONST('/'), RegExp::PLUS('*'), RegExp::STAR(RegExp::AND({RegExp::EXCEPT({'/','*'}), RegExp::STAR(RegExp::EXCEPT({'*'})),RegExp::PLUS('*') })), RegExp::CONST('/') })), ELexerAction::SKIP);
		LexConfig.Add("WS", new RegExp(RegExp::PLUS(RegExp::LIST({ ' ', RegExp::TAB, RegExp::CR, RegExp::LF }))), ELexerAction::SKIP);

		/*Lexer* lex = new Lexer(&LexConfig);
		LexerFactory::Serialize(lex, "res/Lexer.lex");

		std::cout << "Input of \"" << SourceCode << "\"" << std::endl << "results in:" << std::endl;
		std::vector<Token*> TokenList = lex->Tokenize(SourceCode);
		std::cout << TokenList << std::endl << std::endl;

		delete lex;*/

		ParserConfig ParsConfig = ParserConfig();
		//ParsConfig.AddProduction("root", { "rulelist", "EOF" });

		ParsConfig.AddProduction("rulelist", { "parserrule", "rulelist" });
		ParsConfig.AddProduction("rulelist", { "lexerrule", "rulelist" });
		ParsConfig.AddProduction("rulelist", { EOS_S });

		ParsConfig.AddProduction("parserrule", { "PARSERID", "COLON", "parseror", "SEMICOLON" });

		ParsConfig.AddProduction("parseror", { "parserlist", "parseror2" });
		ParsConfig.AddProduction("parseror2", { "PIPE", "parserlist", "parseror2" });
		//ParsConfig.AddProduction("parseror2", { "PIPE", "parseror2" });
		ParsConfig.AddProduction("parseror2", { EPSILON_S });

		//ParsConfig.AddProduction("parserlist", { "parserconst",  "parserlist2" });
		//ParsConfig.AddProduction("parserlist2", { "parserconst", "parserlist2" });
		//ParsConfig.AddProduction("parserlist2", { EPSILON_S });

		ParsConfig.AddProduction("parserlist", { "parserconst",  "parserlist" });
		ParsConfig.AddProduction("parserlist", { EPSILON_S });

		ParsConfig.AddProduction("parserconst", { "LEXERID" });
		ParsConfig.AddProduction("parserconst", { "PARSERID" });
		ParsConfig.AddProduction("parserconst", { "LITERAL" });
		ParsConfig.AddProduction("parserconst", { "LEFTPARENTHESE", "parseror", "RIGHTPARENTHESE" });



		ParsConfig.AddProduction("lexerrule", { "LEXERID", "COLON" ,"regex", "action", "SEMICOLON" });

		ParsConfig.AddProduction("action", { "ARROW", "PARSERID" });
		ParsConfig.AddProduction("action", { EPSILON_S });

		ParsConfig.AddProduction("regex", { "lexeror", "regex" });
		ParsConfig.AddProduction("regex", { EPSILON_S });

		ParsConfig.AddProduction("lexeror", { "operator", "lexeror2" });
		ParsConfig.AddProduction("lexeror2", { "PIPE", "operator", "lexeror2" });
		ParsConfig.AddProduction("lexeror2", { EPSILON_S });

		ParsConfig.AddProduction("operator", { "lexerconst", "operator2" });
		ParsConfig.AddProduction("operator2", { "STAR" });
		ParsConfig.AddProduction("operator2", { "PLUS" });
		ParsConfig.AddProduction("operator2", { "QUESTIONMARK" });
		ParsConfig.AddProduction("operator2", { EPSILON_S });

		/*ParsConfig.AddProduction("anytime", { "STAR" });
		ParsConfig.AddProduction("once", { "PLUS" });
		ParsConfig.AddProduction("optional", { "QUESTIONMARK" });*/

		ParsConfig.AddProduction("lexerconst", { "LEFTPARENTHESE", "regex", "RIGHTPARENTHESE" });
		//ParsConfig.AddProduction("lexerconst", { "range" });
		ParsConfig.AddProduction("lexerconst", { "LEXERID" });
		ParsConfig.AddProduction("lexerconst", { "DOT" });
		ParsConfig.AddProduction("lexerconst", { "CHARSET" });
		ParsConfig.AddProduction("lexerconst", { "LITERAL" });

		//ParsConfig.AddProduction("range", { "LITERAL", ".." ,"LITERAL" });

		//Parser pars(&ParsConfig);
		//ParserFactory::Serialize(&pars, "res/Parser.par");
		//ParseTree* Tree = pars.BuildTree(TokenList);

		/*TestParser* Parser = new TestParser(TokenList);
		Rule_parserrule* ParseTree;
		Parser->Parserrule(ParseTree);
		delete ParseTree;*/



		//ParserBuilder builder(&ParsConfig, &LexConfig);


		TestLexer* lex = new TestLexer(SourceCode);
		const std::vector<Token*>& TokenStream = lex->GetTokenStream();
		std::cout << TokenStream << std::endl << std::endl;

		TestParser* pars = new TestParser(TokenStream);
		Rule_rulelist* root;
		pars->Rulelist(root);

		TestVisitor* vis = new TestVisitor();
		if (vis->Visit(root))
		{
			ParserBuilder builder(vis->GetParserConfig(), vis->GetLexerConfig());
			builder.Generate("src/gen/", "Test");
		}
		else
		{
			std::cout << "Failed to Analyse Parse Tree" << std::endl;
		}

		delete lex;
		delete pars;
		delete root;
		delete vis;
	}

	void App::ListParser(const std::string& SourceCode)
	{
		LexerConfig LexConfig;
		LexConfig.Add("MINUS", new RegExp(RegExp::CONST('-')));
		LexConfig.Add("ESCAPED", new RegExp(RegExp::AND('\\', RegExp::ANY())));
		LexConfig.Add("CHAR", new RegExp(RegExp::ANY()));

		ParserConfig ParsConfig = ParserConfig();
		ParsConfig.AddProduction("elements", { "range", "elements" });
		ParsConfig.AddProduction("elements", { EOS_S });
		ParsConfig.AddProduction("range", { "symbol", "range2" });
		ParsConfig.AddProduction("range2", { "MINUS", "symbol" });
		ParsConfig.AddProduction("range2", { EPSILON_S });
		ParsConfig.AddProduction("symbol", { "MINUS" });
		ParsConfig.AddProduction("symbol", { "CHAR" });
		ParsConfig.AddProduction("symbol", { "ESCAPED" });

		ParserBuilder builder(&ParsConfig, &LexConfig);
	}

}



