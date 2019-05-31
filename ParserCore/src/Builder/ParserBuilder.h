#pragma once
#include <string>

#include "../Lexer/LexerConfig.h"
#include "../Parser/ParserConfig.h"
#include "Alphabet.h"
#include "../Parser/ParseTable/ParsingTable.h"
#include "../Lexer/Automaton/Automaton.h"

namespace ParserGenerator {

	class ParserBuilder
	{
	protected:
		Alphabet* m_Alphabet;
		Automaton::DFA* m_DFA;
		ParseTable::ParsingTable* m_Table;

		ParserConfig* m_ParsConfig;
		LexerConfig* m_LexConfig;

	public:
		ParserBuilder(ParserConfig* InParsConfig, LexerConfig* InLexConfig);
		~ParserBuilder();

		void Generate(const std::string& RootPath, const std::string& GrammarName);
		// Serialize DFA/Table
		// Generate Files
	};

}