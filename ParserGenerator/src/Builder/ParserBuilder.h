#pragma once
#include <string>

#include "../Lexer/LexerConfig.h"
#include "../Parser/ParserConfig.h"
#include "Alphabet.h"
#include "../Parser/ParsingTable.h"
#include "../Lexer/Automaton/Automaton.h"

namespace ParserGenerator {

	class ParserBuilder
	{
	protected:
		Alphabet* m_Alphabet;
		Automaton::DFA* m_DFA;
		ParsingTable* m_Table;

	public:
		ParserBuilder(ParserConfig* ParsConfig, LexerConfig* LexConfig);
		~ParserBuilder();

		void Generate(const std::string& RootPath);
		// Serialize DFA/Table
		// Generate Files
	};

}