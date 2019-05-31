// Automatically generated File
#include "GenLexer.h"


GenLexer::GenLexer(const std::string& InSourceCode)
	: Lexer(InSourceCode)
{
	Init();
}

const char* GenLexer::GetSerializedAutomaton() const
{
	return "13 0 2 1 2 3 2 4 2 2 -1 5 4 6 6 7 7 8 3 9 5 10 8 11 0 12 0 13 -1\n0 1 48 49 50 51 52 53 54 55 56 57\n0 2 46\n1 1 48 49 50 51 52 53 54 55 56 57\n1 2 46\n3 3 48 49 50 51 52 53 54 55 56 57\n4 3 48 49 50 51 52 53 54 55 56 57\n2 4 48 49 50 51 52 53 54 55 56 57\n11 12 9 10 13 32\n12 12 9 10 13 32\n13 0 48 49 50 51 52 53 54 55 56 57\n13 11 9 10 13 32\n13 5 40\n13 7 43\n13 8 41\n13 10 42\n13 9 47\n13 6 45\n";
}

std::set<int> GenLexer::GetHiddenTokenTypes() const
{
	return { ETokenType::WS, };
}
