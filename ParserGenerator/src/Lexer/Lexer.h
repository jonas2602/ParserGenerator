#pragma once

#include <string>
#include <vector>

#include "StateMachine.h"
#include "RegExp.h"
#include "LexerConfig.h"
#include "Token.h"

namespace ParserGenerator {

	class Lexer
	{
	protected:
		StateMachine m_NFA;
		StateMachine m_DFA;

		LexerConfig* m_Config;

	public:
		Lexer(LexerConfig* InConfig);
		~Lexer();

		std::vector<Token*> Tokenize(const std::string& SourceCode) const;


	};

}