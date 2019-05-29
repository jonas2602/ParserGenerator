// Automatically generated File
#include "GenLexer.h"


GenLexer::GenLexer(const std::string& InSourceCode)
	: Lexer(InSourceCode)
{
	Init();
}

const char* GenLexer::GetSerializedAutomaton() const
{
	return "5 0 2 2 2 3 2 4 2 1 -1 5 -1 11 4 8 6 7 7 12 3 10 5 9 8 6 0 13 0\n0 0 48 49 50 51 52 53 54 55 56 57\n0 1 46\n2 0 48 49 50 51 52 53 54 55 56 57\n2 1 46\n3 4 48 49 50 51 52 53 54 55 56 57\n4 4 48 49 50 51 52 53 54 55 56 57\n1 3 48 49 50 51 52 53 54 55 56 57\n5 6 9 10 13 32\n5 2 48 49 50 51 52 53 54 55 56 57\n5 7 43\n5 8 45\n5 9 42\n5 10 47\n5 11 40\n5 12 41\n6 13 9 10 13 32\n13 13 9 10 13 32\n";
}

std::set<int> GenLexer::GetHiddenTokenTypes() const
{
	return { ETokenType::WS, };
}
