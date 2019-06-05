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
		return "2 0 3 1 5 2 -1 9 -1 11 1 10 1 8 1 12 1 6 6 3 2 4 4 5 7 7 0 13 0\n2 3 41\n2 4 47\n2 0 40\n2 5 42\n2 6 43\n2 1 45\n2 7 9 10 13 32\n2 8 48 49 50 51 52 53 54 55 56 57\n9 10 48 49 50 51 52 53 54 55 56 57\n11 11 48 49 50 51 52 53 54 55 56 57\n10 11 48 49 50 51 52 53 54 55 56 57\n8 12 48 49 50 51 52 53 54 55 56 57\n8 9 46\n12 12 48 49 50 51 52 53 54 55 56 57\n12 9 46\n7 13 9 10 13 32\n13 13 9 10 13 32\n";
	}

	std::set<int> GenLexer::GetHiddenTokenTypes() const
	{
		return { ETokenType::WS, };
	}
}
