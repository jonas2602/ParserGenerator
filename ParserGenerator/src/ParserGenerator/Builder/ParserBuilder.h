#pragma once
#include <string>

#include "../Interpreter/LexerConfig.h"
#include "../Interpreter/ParserConfig.h"
#include "Alphabet.h"
#include <ParserCore.h>
#include "../Regex/NFA.h"

namespace ParserGenerator {

	class ParserBuilder
	{
	protected:
		Alphabet* m_Alphabet;
		PCA::DFA* m_DFA;
		PCT::ParsingTable* m_Table;

		ParserConfig* m_ParsConfig;
		LexerConfig* m_LexConfig;

		bool bValidGrammar = false;

	public:
		ParserBuilder(const std::string& InSourceCode);
		~ParserBuilder();

		void Generate(const std::string& InRootPath, const std::string& InGrammarName, const std::string& InNamespaceName = "");

	protected:
		bool CreateConfigsFromSource(const std::string& InSourceCode);
		bool CreateAutomaton();
		bool CreateParsingTable();
	};

}