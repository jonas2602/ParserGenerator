#pragma once
#include <string>

#include <ParserCore.h>
#include "Alphabet.h"
#include "../Interpreter/ParserConfig.h"
#include "../Interpreter/LexerConfig.h"
#include "../Serializer/CodeGenerator.h"

namespace ParserGenerator {

	class ParserSerializer
	{
	protected:
		std::string m_ParserName;
		std::string m_NamespaceName;
		std::string m_DirPath;
		std::string m_CodePath;
		std::string m_DocuPath;

		CodeGenerator* m_Generator;

	public:
		ParserSerializer(const std::string& InDirPath, const std::string& InParserName = "New", const std::string& InNamespaceName = "", const std::string& InCodePath = "", const std::string& InDocuPath = "");
		~ParserSerializer();

	public:
		// Human readable Versions (Doku)
		bool WriteAlphabetDoc(Alphabet* InAlphabet) const;
		bool WriteParsingTableDoc(PCT::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteAutomatonDoc(PCA::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet);

		// Code used in the final application
		bool WriteAlphabetCode(Alphabet* InAlphabet) const;
		bool WriteRuleCode(ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteLexerCode(PCA::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet) const;
		bool WriteParserCode(PCT::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const;
		bool WriteVisitorCode(Alphabet* InAlphabet) const;

		void Finish() const;

	protected:

		// Versions stored in the Lexer/Parser class, used at runtime
		bool SerializeParsingTable(PCT::ParsingTable* InTable, std::string& OutString) const;
		bool SerializeAutomaton(PCA::DFA* InDFA, std::string& OutString) const;

		// Helper functions
		void WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream) const;
		void WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream) const;

		std::string ExtendFileName(const std::string& RawFileName) const;
	};

}