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
		return "2 0 4 1 7 2 -1 5 8 7 3 3 6 4 9 6 -1 8 -1 9 -1 10 -1 11 5\n2 3 47\n2 4 42\n2 1 45\n2 5 43\n2 0 40\n2 6 97\n2 7 41\n6 8 98\n8 9 99\n9 10 10\n10 11 39\n";
	}

	std::set<int> GenLexer::GetHiddenTokenTypes() const
	{
		return { ETokenType::WS, };
	}
}
