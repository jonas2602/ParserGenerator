#include "ParserSerializer.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "../ParserTypes.h"

namespace ParserGenerator {
	ParserSerializer::ParserSerializer(const std::string& InDirPath, const std::string& InParserName, const std::string& InCodePath, const std::string& InDocuPath)
		: m_DirPath(InDirPath), m_ParserName(InParserName), m_CodePath(InCodePath), m_DocuPath(InDocuPath)
	{
		m_Generator = new CodeGenerator(InDirPath);
	}

	bool ParserSerializer::WriteAlphabetDoc(Alphabet* InAlphabet) const
	{
		// Create Output Streams
		std::stringstream TokenStream;
		ParserSerializer::WriteTokenList(InAlphabet, TokenStream);
		std::stringstream NonTerminalStream;
		ParserSerializer::WriteNonTerminalList(InAlphabet, NonTerminalStream);

		std::string FileName = ExtendFileName("Alphabet");
		std::ofstream File;
		if (!m_Generator->GetFileStream(FileName, File, m_DocuPath))
		{
			std::cout << "Failed to open File " << FileName << std::endl;
			return false;
		}

		File << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		File << TokenStream.str();
		File << std::endl;
		File << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		File << NonTerminalStream.str();
		File << std::endl;

		return false;
	}



	bool ParserSerializer::WriteParsingTable(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet, const std::string& FilePath)
	{
		// Create Output Streams
		std::stringstream TokenStream;
		ParserSerializer::WriteTokenList(InAlphabet, TokenStream);
		std::stringstream NonTerminalStream;
		ParserSerializer::WriteNonTerminalList(InAlphabet, NonTerminalStream);
		std::stringstream TableStream;
		std::stringstream RuleStream;

		// Write Rules
		for (ParserConfigElement* Production : ParsConfig->GetProductionList())
		{
			RuleStream << Production->m_LocalRuleIndex << " " << Production->m_NonTerminal << "(" << InAlphabet->GetNonTerminalIndex(Production->m_NonTerminal) << ") ->";
			for (const std::string& TokenClass : Production->m_TokenClasses)
			{
				int ElementIndex = -1;
				if (InAlphabet->IsNonTerminal(TokenClass)) ElementIndex = InAlphabet->GetNonTerminalIndex(TokenClass);
				else if (InAlphabet->IsToken(TokenClass)) ElementIndex = InAlphabet->GetTokenIndex(TokenClass);

				const std::string& ElementName = IsEpsilon(TokenClass) ? "EPSILON" : TokenClass;

				RuleStream << " " << ElementName << "(" << ElementIndex << ")";
			}

			RuleStream << std::endl;
		}

		// Write ParseTable
		for (const std::pair<int, std::map<int, int>>& NonTerminalPair : InTable->GetProductionMap())
		{
			for (const std::pair<int, int>& TokenPair : NonTerminalPair.second)
			{
				const std::string& NonTerminalName = InAlphabet->GetNonTerminalName(NonTerminalPair.first);
				const std::string& TokenName = InAlphabet->GetTokenName(TokenPair.first);

				const std::vector<std::string>& RuleElementList = ParsConfig->GetRuleElements(NonTerminalName, TokenPair.second);
				TableStream << "[" << NonTerminalName << "(" << NonTerminalPair.first << "), " << TokenName << "(" << TokenPair.first << ")] -> " << TokenPair.second;

				for (const std::string& RuleElement : RuleElementList)
				{
					TableStream << " " << (IsEpsilon(RuleElement) ? "EPSILON" : RuleElement);
				}

				TableStream << std::endl;
			}
		}


		// Write to File
		std::ofstream File(FilePath);
		if (!File.is_open())
		{
			std::cout << "Failed to open File " << FilePath << std::endl;
			return false;
		}

		File << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		File << TokenStream.str();
		File << std::endl;
		File << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		File << NonTerminalStream.str();
		File << std::endl;
		File << "Table Entries:" << std::endl << "([NonTerminal], [Token]) -> [Rule]" << std::endl;
		File << TableStream.str();
		File << std::endl;
		File << "Rules:" << std::endl << "[LocalRuleIndex] [NonTerminal] -> [Element] [Element] ..." << std::endl;
		File << RuleStream.str();

		return true;
	}

	bool ParserSerializer::WriteAutomaton(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet, const std::string& FilePath)
	{
		// Create Output Streams
		std::stringstream TokenStream;
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		// Write Token Data
		int TokenIndex = 0;
		for (const LexerConfigElement& TokenType : LexConfig->GetRegexList())
		{
			TokenStream << TokenIndex++ << " " << TokenType.m_Name << " " << TokenType.m_Action << std::endl;
		}

		std::map<Automaton::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, Automaton::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			Automaton::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << ActiveIndex << " " << ActiveState->GetName() << " " << ActiveState->GetStatePriority() << std::endl;

			// Write Transition Data
			for (Automaton::Transition* Trans : ActiveState->GetTransitions())
			{
				Automaton::State* OtherState = Trans->GetTargetState();
				int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = StateIndex++;
				TransitionStream << ActiveIndex << " " << OtherIndex;

				// Write Condition Data
				for (const char& Symbol : Trans->GetCondition())
				{
					TransitionStream << " " << (int)Symbol;
				}

				TransitionStream << std::endl;
			}
		}

		const std::string& StartStateName = InDFA->GetStartState()->GetName();
		int StartStateIndex = IndexMap[InDFA->GetStartState()];

		// Write to File
		std::ofstream File(FilePath);
		if (!File.is_open())
		{
			std::cout << "Failed to open File " << FilePath << std::endl;
			return false;
		}

		File << "Avaliable Tokens:" << std::endl << "[Index] [Name] [Action]" << std::endl;
		File << TokenStream.str();
		File << std::endl;
		File << "Automaton States:" << std::endl << "[Index] [Symbolic Name] [Priority]" << std::endl;
		File << StateStream.str();
		File << std::endl;
		File << "Automaton Transitions:" << std::endl << "[Start State] [End State] [Condition chars]" << std::endl;
		File << TransitionStream.str();
		File << std::endl;
		File << "Automaton Start State:" << std::endl << "[Index] [Symbolic Name]" << std::endl;
		File << StartStateIndex << " " << StartStateName;

		return true;
	}

	bool ParserSerializer::SerializeParsingTable(ParseTable::ParsingTable* InTable, std::string& OutString)
	{
		std::stringstream OutStream;

		for (const std::pair<int, std::map<int, int>>& NonTerminalPair : InTable->GetProductionMap())
		{
			for (const std::pair<int, int>& TokenPair : NonTerminalPair.second)
			{
				// List of tripples (nonterminal, token, localruleindex)
				OutStream << NonTerminalPair.first << " " << TokenPair.first << " " << TokenPair.second << " ";
			}
		}

		OutString = OutStream.str();
		return true;
	}

	bool ParserSerializer::SerializeAutomaton(Automaton::DFA* InDFA, std::string& OutString)
	{
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		std::map<Automaton::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, Automaton::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			Automaton::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << " " << ActiveIndex << " " << ActiveState->GetStatePriority();

			// Write Transition Data
			for (Automaton::Transition* Trans : ActiveState->GetTransitions())
			{
				Automaton::State* OtherState = Trans->GetTargetState();
				int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = StateIndex++;
				TransitionStream << ActiveIndex << " " << OtherIndex;

				// Write Condition Data
				for (const char& Symbol : Trans->GetCondition())
				{
					TransitionStream << " " << (int)Symbol;
				}

				TransitionStream << "\\n";
			}
		}

		// start state
		int StartIndex = IndexMap[InDFA->GetStartState()];

		OutString = std::to_string(StartIndex) + StateStream.str() + "\\n" + TransitionStream.str();
		return true;
	}

	bool ParserSerializer::WriteAlphabetCode(Alphabet* InAlphabet) const
	{
		std::string FileName = ExtendFileName("Alphabet");
		std::ofstream HeaderFile;
		if (!m_Generator->GetCodeFileStreams(m_CodePath, FileName, &HeaderFile))
		{
			std::cout << "Failed to open File " << FileName << std::endl;
			return false;
		}
		
		CodeSnippet_Enum TokenEnum("ETokenType", InAlphabet->GetTokenMap());
		TokenEnum.Write(m_Generator, HeaderFile, HeaderFile, nullptr);

		CodeSnippet_Enum RuleEnum("ERuleType", InAlphabet->GetNonTerminalMap());
		RuleEnum.Write(m_Generator, HeaderFile, HeaderFile, nullptr);

		return true;
	}

	void ParserSerializer::WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream)
	{
		const std::vector<std::string>& TokenList = InAlphabet->GetTokenList();
		for (int i = 0; i < TokenList.size(); i++)
		{
			TokenStream << i << " " << TokenList[i] << std::endl;
		}
	}

	void ParserSerializer::WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream)
	{
		const std::vector<std::string>& NonTerminalList = InAlphabet->GetNonTerminalList();
		for (int i = 0; i < NonTerminalList.size(); i++)
		{
			NonTerminalStream << i << " " << NonTerminalList[i] << std::endl;
		}
	}

	std::string ParserSerializer::ExtendFileName(const std::string& RawFileName) const
	{
		return m_ParserName + RawFileName;
	}

}