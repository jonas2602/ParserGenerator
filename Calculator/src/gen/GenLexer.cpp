// Automatically generated File
#include "GenLexer.h"


namespace Gen {

	GenLexer::GenLexer(const std::string& InSourceCode)
		: Lexer(InSourceCode)
	{
		Init();
	}

	const char* GenLexer::GetSerializedAutomaton() const
	{
		return "11 0 2 2 2 3 2 4 2 1 -1 5 4 6 7 7 8 8 3 9 6 10 9 11 -1 12 -1 14 -1 15 -1 16 -1 17 5 18 0 13 0\n0 1 46\n0 2 48 49 50 51 52 53 54 55 56 57\n2 1 46\n2 2 48 49 50 51 52 53 54 55 56 57\n3 4 48 49 50 51 52 53 54 55 56 57\n4 4 48 49 50 51 52 53 54 55 56 57\n1 3 48 49 50 51 52 53 54 55 56 57\n11 7 43\n11 6 45\n11 9 47\n11 0 48 49 50 51 52 53 54 55 56 57\n11 10 42\n11 8 41\n11 12 97\n11 5 40\n11 13 9 10 13 32\n12 14 98\n14 15 99\n15 16 10\n16 17 39\n18 18 9 10 13 32\n13 18 9 10 13 32\n";
	}

	std::set<int> GenLexer::GetHiddenTokenTypes() const
	{
		return { ETokenType::WS, };
	}
}
