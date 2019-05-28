#pragma once
#include <string>
#include "Alphabet.h"
#include "../Parser/ParseTable/ParsingTable.h"
#include "../Parser/ParserConfig.h"
#include "../Lexer/LexerConfig.h"
#include "../Lexer/Automaton/Automaton.h"
#include "../Generator/CodeGenerator.h"

namespace ParserGenerator {

	class ParserSerializer
	{
	protected:
		std::string m_ParserName;
		std::string m_DirPath;
		std::string m_CodePath;
		std::string m_DocuPath;

		CodeGenerator* m_Generator;

	public:
		ParserSerializer(const std::string& InDirPath, const std::string& InParserName = "New", const std::string& InCodePath = "", const std::string& InDocuPath = "");

	public:
		// Human readable Versions (Doku)
		bool WriteAlphabetDoc(Alphabet* InAlphabet) const;
		bool WriteParsingTableDoc(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteAutomatonDoc(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet);

		// Versions stored in the Lexer/Parser class, used at runtime
		static bool SerializeParsingTable(ParseTable::ParsingTable* InTable, std::string& OutString);
		static bool SerializeAutomaton(Automaton::DFA* InDFA, std::string& OutString);

		// Code used in the final application
		bool WriteAlphabetCode(Alphabet* InAlphabet) const;
		bool WriteRuleCode(ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteLexerCode(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet) const;
		bool WriteParserCode(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteVisitorCode(ParserConfig* ParsConfig) const;

		void Finish() const;

	protected:
		// Helper functions
		static void WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream);
		static void WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream);

		std::string ExtendFileName(const std::string& RawFileName) const;
	};

}