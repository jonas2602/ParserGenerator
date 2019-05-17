#pragma once

#include <string>
#include <vector>

#include "Automaton/Automaton.h"
#include "RegExp.h"
#include "LexerConfig.h"
#include "Token.h"

namespace ParserGenerator {

	class Lexer
	{
	protected:
		Automaton::NFA* m_NFA;
		Automaton::DFA* m_DFA;

		LexerConfig* m_Config;

	public:
		Lexer(LexerConfig* InConfig);
		~Lexer();

		std::vector<Token*> Tokenize(const std::string& SourceCode) const;

		bool Serialize(const std::string& FilePath) const;

	};

}