#include "ListInterpreter.h"
#include "ListLexer.h"
#include "ListAlphabet.h"

void ListInterpreter::Analyse(const std::string& ListContent, std::vector<ParserGenerator::Node_CONST*>& OutNodes)
{
	std::vector<ParserGenerator::Token*> TokenStream = ListLexer(ListContent).GetTokenStream();

	for (int i = 1; i < TokenStream.size();)
	{
		ParserGenerator::Token* CenterToken = TokenStream[i];
		if (CenterToken->GetTokenType() == ETokenType::MINUS && i < (TokenStream.size() - 2))
		{
			// Create Range
			char LeftBorder = GetTokenSymbol(TokenStream[i - 1]);
			char RightBorder = GetTokenSymbol(TokenStream[i + 1]);
			OutNodes.push_back(ParserGenerator::RegExp::RANGE(LeftBorder, RightBorder));
			i += 3;
		}
		else
		{
			// Create Single Element
			char TokenSymbol = GetTokenSymbol(TokenStream[i - 1]);
			OutNodes.push_back(ParserGenerator::RegExp::CONST(TokenSymbol));
			i += 1;
		}
	}
}

char ListInterpreter::GetTokenSymbol(ParserGenerator::Token* InToken)
{
	if (InToken->GetTokenType() == ETokenType::ESCAPED)
	{
		return InToken->GetTokenData()[InToken->GetTokenData().size() - 1];
	}
	else
	{
		return InToken->GetTokenData()[0];
	}
}
