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
		
		// Create File
		std::string FileName = ExtendFileName("Alphabet");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream(); 
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << NonTerminalStream.str();
		OutStream << std::endl;

		return true;
	}



	bool ParserSerializer::WriteParsingTableDoc(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const
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

		// Table that is used in Parser
		std::string TableString;
		ParserSerializer::SerializeParsingTable(InTable, TableString);


		// Create File
		std::string FileName = ExtendFileName("ParsingTable");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream();
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << NonTerminalStream.str();
		OutStream << std::endl;
		OutStream << "Table Entries:" << std::endl << "([NonTerminal], [Token]) -> [Rule]" << std::endl;
		OutStream << TableStream.str();
		OutStream << std::endl;
		OutStream << "Rules:" << std::endl << "[LocalRuleIndex] [NonTerminal] -> [Element] [Element] ..." << std::endl;
		OutStream << RuleStream.str();
		OutStream << std::endl;
		OutStream << "Serialized Parsing Table:" << std::endl << "[NonTerminal] [Token] [LocalRuleIndex] ..." << std::endl;
		OutStream << TableString;

		return true;
	}

	bool ParserSerializer::WriteAutomaton(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet)
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

		// Table that is used in Parser
		std::string AutomatonString;
		ParserSerializer::SerializeAutomaton(InDFA, AutomatonString);

		// Create File
		std::string FileName = ExtendFileName("Automaton");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream();
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name] [Action]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Automaton States:" << std::endl << "[Index] [Symbolic Name] [Priority]" << std::endl;
		OutStream << StateStream.str();
		OutStream << std::endl;
		OutStream << "Automaton Transitions:" << std::endl << "[Start State] [End State] [Condition chars]" << std::endl;
		OutStream << TransitionStream.str();
		OutStream << std::endl;
		OutStream << "Automaton Start State:" << std::endl << "[Index] [Symbolic Name]" << std::endl;
		OutStream << StartStateIndex << " " << StartStateName << std::endl;
		OutStream << std::endl;
		OutStream << "Serialized Deterministic Finite Automaton:" << std::endl;
		OutStream << AutomatonString;

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
		// Create File
		std::string FileName = ExtendFileName("Alphabet");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		
		// Add Enums
		AlphabetFile->AddSnippet(new CodeSnippet_Enum("ETokenType", InAlphabet->GetTokenMap()));
		AlphabetFile->AddSnippet(new CodeSnippet_Enum("ERuleType", InAlphabet->GetNonTerminalMap()));
		
		return true;
	}

	void ParserSerializer::Finish() const
	{
		m_Generator->GenerateFiles();
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