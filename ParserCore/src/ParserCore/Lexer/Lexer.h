#pragma once

#include <string>
#include <vector>

#include "Automaton/Automaton.h"
#include "Token.h"

#include "../Core.h"

namespace ParserCore {

	class LineTracker {
	protected:
		bool m_bZeroBased;

		int m_TotalCount;
		int m_Line;
		int m_Column;

	public:
		LineTracker(bool InZeroBased = false)
			: m_bZeroBased(InZeroBased)
		{
			m_TotalCount = 0;
			m_Line = 1;
			m_Column = 0;
		}

		int GetTotalCount() const { return m_TotalCount; }
		int GetLine() const { return m_Line; }
		int GetColumn() const { return m_Column; }

	public:
		void Analyze(const std::string& InData);

		//bool HasNext();
		//bool Next();
		//const char& Get();

		//void Fallback();
		//void Confirm();
	};

	class PARSER_API Lexer
	{
	protected:
		Automaton::DFA* m_DFA;
		std::set<int> m_HiddenTypes;

		std::vector<Token*> m_TokenStream;
		std::string m_SourceCode;
		// std::vector<LexerConfigElement> m_TokenTypes;

		LineTracker Tracker;
		//std::string::iterator m_StartSymbol;
		//Automaton::State* m_ActiveState;
		//std::string::const_iterator m_SymbolIterator;

		//int m_ConfirmedTokenLength;
		//Automaton::State* m_ConfirmedFinalState;

		//int EnhancedLineCounter = 1;
		//int EnhancedCharCount = 1;
		//int EnhancedTotalCounter = 1;

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

		/*void CreateToken();
		bool ValidateActiveState();
		bool TryStepAutomaton();
		void Fallback();

		void FindFinalState();*/

		bool IsVisibleToken(int TokenType) const { return m_HiddenTypes.find(TokenType) == m_HiddenTypes.end(); }

		virtual const char* GetSerializedAutomaton() const = 0;
		virtual std::set<int> GetHiddenTokenTypes() const = 0;

	public:
		const std::vector<Token*>& GetTokenStream() const { return m_TokenStream; }
	};

}