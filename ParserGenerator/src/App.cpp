#include <iostream>
#include <fstream>
#include <sstream>
#include <ParserCore.h>

#include "ParserGenerator/Builder/ParserBuilder.h"

// argv0 = Programname
// argv1 = Grammarpath
// argv2 = Name of the generated LL-Parser
// argv3 = Root Path to generate LL-Parser in
// argv4 = Optional Namespace Name
int main(int argc, char* argv[])
{
	std::cout << "Start Generator" << std::endl;

	//for (int i = 0; i < argc; ++i)
	//	std::cout << argv[i] << std::endl;

	//std::ifstream File("../Calculator/src/calc.g");
	std::ifstream File("./res/GrammarParser.txt");
	std::stringstream buffer;
	buffer << File.rdbuf();
	std::string SourceCode = buffer.str();
	//std::cout << "Grammar:" << std::endl << SourceCode << std::endl << std::endl;

	ParserGenerator::ParserBuilder* Builder = new ParserGenerator::ParserBuilder("123test");
	Builder->Generate("res/gen/", "Grammar");
	//Builder.Generate("../Calculator/src/gen/", "Gen", "Gen");

	std::cin.get();
	delete Builder;

	return 0;
}

// Regenerate self (the LL-Parser that is used in the Parser Generator)
void GenerateParser()
{

}

// TODO: Optional generate Lexer only?