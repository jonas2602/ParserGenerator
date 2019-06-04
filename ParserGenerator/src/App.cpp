#include <iostream>
#include <fstream>
#include <sstream>
#include <ParserCore.h>

#include "ParserGenerator/Builder/ParserBuilder.h"


void testfunction()
{
	std::vector<std::shared_ptr<PC::Token>> testVector;
	testVector.push_back(std::make_shared<PC::Token>("", 1, -1, -1, -1, -1));
	testVector.push_back(std::make_shared<PC::Token>("", 11, -1, -1, -1, -1));
	testVector.push_back(std::make_shared<PC::Token>("", 2, -1, -1, -1, -1));
}

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

	//testfunction();

	//std::ifstream File("../Calculator/src/calc.g");
	std::ifstream File("./res/GrammarParser.txt");
	std::stringstream buffer;
	buffer << File.rdbuf();
	std::string SourceCode = buffer.str();
	//std::cout << "Grammar:" << std::endl << SourceCode << std::endl << std::endl;

	ParserGenerator::ParserBuilder* Builder = new ParserGenerator::ParserBuilder(SourceCode);
	Builder->Generate("res/gen/", "Grammar");
	//Builder.Generate("../Calculator/src/gen/", "Gen", "Gen");

	//std::cin.get();
	delete Builder;

	return 0;
}

// Regenerate self (the LL-Parser that is used in the Parser Generator)
void GenerateParser()
{

}

// TODO: Optional generate Lexer only?