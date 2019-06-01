#pragma once
#include <string>

#include "../Interpreter/LexerConfig.h"
#include "../Interpreter/ParserConfig.h"
//#include "Alphabet.h"
//#include "../Parser/ParseTable/ParsingTable.h"
//#include "../Lexer/Automaton/Automaton.h"

namespace ParserGenerator {

	class ParserBuilder
	{
	protected:
		//Alphabet* m_Alphabet;
		//Automaton::DFA* m_DFA;
		//ParseTable::ParsingTable* m_Table;

		ParserConfig* m_ParsConfig;
		LexerConfig* m_LexConfig;

	public:
		ParserBuilder(const std::string& InSourceCode);
		ParserBuilder(ParserConfig* InParsConfig, LexerConfig* InLexConfig);
		~ParserBuilder();

		void Generate(const std::string& InRootPath, const std::string& InGrammarName, const std::string& InNamespaceName = "");
		// Serialize DFA/Table
		// Generate Files
	};

}