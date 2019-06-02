// Automatically generated File
#include "GenLexer.h"


GenLexer::GenLexer(const std::string& InSourceCode)
	: Lexer(InSourceCode)
{
	Init();
}

const char* GenLexer::GetSerializedAutomaton() const
{
	return "10 0 2 2 2 1 -1 3 2 4 2 5 4 6 7 7 8 8 3 9 6 10 -1 11 9 12 -1 14 -1 15 -1 16 -1 17 5 18 0 13 0\n0 1 46\n0 2 48 49 50 51 52 53 54 55 56 57\n2 1 46\n2 2 48 49 50 51 52 53 54 55 56 57\n1 3 48 49 50 51 52 53 54 55 56 57\n3 4 48 49 50 51 52 53 54 55 56 57\n4 4 48 49 50 51 52 53 54 55 56 57\n10 9 47\n10 6 45\n10 8 41\n10 7 43\n10 11 42\n10 5 40\n10 12 97\n10 0 48 49 50 51 52 53 54 55 56 57\n10 13 9 10 13 32\n12 14 98\n14 15 99\n15 16 10\n16 17 39\n18 18 9 10 13 32\n13 18 9 10 13 32\n";
}

std::set<int> GenLexer::GetHiddenTokenTypes() const
{
	return { ETokenType::WS, };
}
