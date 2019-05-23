#pragma once

#include <string>
#include <vector>

#include "Automaton/Automaton.h"
#include "RegExp.h"
#include "LexerConfig.h"
#include "Token.h"

#include "../Core.h"

namespace ParserGenerator {

	class Lexer
	{
	protected:
		Automaton::DFA* m_DFA;
		std::set<int> m_HiddenTypes;

		std::vector<Token*> m_TokenStream;
		std::string m_SourceCode;
		// std::vector<LexerConfigElement> m_TokenTypes;

	public:
		// Lexer(LexerConfig* InConfig);
		// Lexer(Automaton::DFA* InDFA, const std::vector<LexerConfigElement>& InTokenTypes);
		Lexer(const std::string& InSourceCode);
		~Lexer();

		// Automaton::DFA* GetDFA() const { return m_DFA; }
		// const std::vector<LexerConfigElement>& GetTokenTypes() const { return m_TokenTypes; }

	protected:
		void Init();

		void LoadAutomaton();
		void Tokenize();

		virtual std::string GetSerializedAutomaton() const = 0;
		virtual std::set<int> GetHiddenTokenTypes() const = 0;

	public:
		const std::vector<Token*>& GetTokenStream() const { return m_TokenStream; }
	};

}