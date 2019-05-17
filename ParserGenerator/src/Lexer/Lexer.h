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
		Automaton::DFA* m_DFA;
		std::vector<LexerConfigElement> m_TokenTypes;

	public:
		Lexer(LexerConfig* InConfig);
		Lexer(Automaton::DFA* InDFA, const std::vector<LexerConfigElement>& InTokenTypes);
		~Lexer();

		Automaton::DFA* GetDFA() const { return m_DFA; }
		const std::vector<LexerConfigElement>& GetTokenTypes() const { return m_TokenTypes; }

	public:
		std::vector<Token*> Tokenize(const std::string& SourceCode) const;
	};

}