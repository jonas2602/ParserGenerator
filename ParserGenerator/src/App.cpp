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
	if (argc < 4)
	{
		std::cout << "Parser Generator requires at least 3 Arguments (Grammar Path, Target Directory, Grammar Name)" << std::endl;
		return 1;
	}

	std::cout << "Start Generator" << std::endl;

	std::string FilePath = "./res/GrammarParser.txt";
	std::string TargetDirectory = "res/gen/";
	std::string GrammarName = "Gen";
	std::string NamespaceName = "";

	if (argc > 1) { FilePath = argv[1]; }
	if (argc > 2) { TargetDirectory = argv[2]; }
	if (argc > 3) { GrammarName = argv[3]; }
	if (argc > 4) { NamespaceName = argv[4]; }
	std::cout << "FilePath: '" << FilePath << "'" << std::endl
		<< "TargetDirectory: '" << TargetDirectory << "'" << std::endl
		<< "GrammarName: '" << GrammarName << "'" << std::endl
		<< "NamespaceName: '" << NamespaceName << "'" << std::endl;

	//std::ifstream File("../Calculator/src/calc.g");
	std::ifstream File(FilePath);
	std::stringstream buffer;
	buffer << File.rdbuf();
	std::string SourceCode = buffer.str();
	//std::cout << "Grammar:" << std::endl << SourceCode << std::endl << std::endl;

	ParserGenerator::ParserBuilder Builder(SourceCode);
	Builder.Generate(TargetDirectory, GrammarName, NamespaceName);

	//std::cin.get();

	return 0;
}

// Regenerate self (the LL-Parser that is used in the Parser Generator)
void GenerateParser()
{

}

// TODO: Optional generate Lexer only?