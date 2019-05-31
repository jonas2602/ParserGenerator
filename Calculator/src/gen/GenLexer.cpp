// Automatically generated File
#include "GenLexer.h"


GenLexer::GenLexer(const std::string& InSourceCode)
	: Lexer(InSourceCode)
{
	Init();
}

const char* GenLexer::GetSerializedAutomaton() const
{
	return "7 0 2 1 -1 3 2 2 2 4 2 5 4 6 6 7 -1 12 7 9 3 10 5 11 8 8 0 13 0\n0 0 48 49 50 51 52 53 54 55 56 57\n0 1 46\n1 2 48 49 50 51 52 53 54 55 56 57\n3 3 48 49 50 51 52 53 54 55 56 57\n2 3 48 49 50 51 52 53 54 55 56 57\n4 0 48 49 50 51 52 53 54 55 56 57\n4 1 46\n7 4 48 49 50 51 52 53 54 55 56 57\n7 8 9 10 13 32\n7 9 41\n7 5 40\n7 10 47\n7 6 45\n7 11 42\n7 12 43\n8 13 9 10 13 32\n13 13 9 10 13 32\n";
}

std::set<int> GenLexer::GetHiddenTokenTypes() const
{
	return { ETokenType::WS, };
}
