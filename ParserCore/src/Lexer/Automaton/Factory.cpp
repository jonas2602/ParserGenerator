#include "Factory.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace ParserCore::Automaton {

	//bool LexerFactory::Serialize(Lexer* InLexer, const std::string& FilePath)
	//{
	//	// Create Output Streams
	//	std::stringstream TokenStream;
	//	std::stringstream StateStream;
	//	std::stringstream TransitionStream;

	//	// Write Token Data
	//	int TokenIndex = 0;
	//	for (const LexerConfigElement& TokenType : InLexer->GetTokenTypes())
	//	{
	//		TokenStream << TokenIndex++ << " " << TokenType.m_Name << " " << TokenType.m_Action << std::endl;
	//	}

	//	std::map<Automaton::State*, int> IndexMap;
	//	int StateIndex = 0;
	//	for (const std::pair<std::string, Automaton::State*>& Element : InLexer->GetDFA()->GetStateMap())
	//	{
	//		// Write State Data
	//		Automaton::State* ActiveState = Element.second;
	//		int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
	//		StateStream << ActiveIndex << " " << ActiveState->GetName() << " " << ActiveState->GetStatePriority() << std::endl;

	//		// Write Transition Data
	//		for (Automaton::Transition* Trans : ActiveState->GetTransitions())
	//		{
	//			Automaton::State* OtherState = Trans->GetTargetState();
	//			int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = StateIndex++;
	//			TransitionStream << ActiveIndex << " " << OtherIndex;

	//			// Write Condition Data
	//			for (const char& Symbol : Trans->GetCondition())
	//			{
	//				TransitionStream << " " << (int)Symbol;
	//			}

	//			TransitionStream << std::endl;
	//		}
	//	}

	//	int StartStateIndex = IndexMap[InLexer->GetDFA()->GetStartState()];

	//	// Write to File
	//	std::ofstream File(FilePath);
	//	if (!File.is_open())
	//	{
	//		std::cout << "Failed to open File " << FilePath << std::endl;
	//		return false;
	//	}

	//	File << TokenStream.str();
	//	File << std::endl;
	//	File << StateStream.str();
	//	File << std::endl;
	//	File << TransitionStream.str();
	//	File << std::endl;
	//	File << StartStateIndex;

	//	return true;
	//}

	//bool LexerFactory::Deserialize(Lexer*& OutLexer, const std::string& FilePath)
	//{
	//	std::ifstream File(FilePath);
	//	if (!File) {
	//		std::cout << "Unable to open file: " << FilePath << std::endl;
	//		return false;
	//	}

	//	std::string Line;

	//	Automaton::DFA* NewAutomaton = new Automaton::DFA();
	//	std::vector<LexerConfigElement> NewTokenList;

	//	// Read Token Lines
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		std::string StateName;
	//		int TokenPriority;
	//		std::string TokenName;
	//		int TokenAction;
	//		if (!(iss >> TokenPriority >> TokenName >> TokenAction))
	//		{
	//			// Reached End of Token List
	//			break;
	//		}

	//		NewTokenList.push_back(LexerConfigElement(TokenName, (ELexerAction)TokenAction));
	//	}

	//	// Read State Lines
	//	std::map<int, Automaton::State*> IndexMap;
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int StateIndex;
	//		std::string StateName;
	//		int StatePriority;
	//		if (!(iss >> StateIndex >> StateName >> StatePriority))
	//		{
	//			// Reached End of State List
	//			break;
	//		}

	//		Automaton::State* NewState = NewAutomaton->CreateNewState(StateName, StatePriority);
	//		IndexMap[StateIndex] = NewState;
	//	}

	//	// Read Transition Lines
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int StartStateIndex;
	//		int EndStateIndex;
	//		std::set<char> Condition;
	//		if (!(iss >> StartStateIndex >> EndStateIndex))
	//		{
	//			// Reached End of Transition List
	//			break;
	//		}

	//		int symbol;
	//		while (iss >> symbol)
	//		{
	//			Condition.insert(char(symbol));
	//		}

	//		NewAutomaton->CreateNewTransition(IndexMap[StartStateIndex], IndexMap[EndStateIndex], Condition);
	//	}

	//	// Read Last Line (Start State Index)
	//	if (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int StartStateIndex;
	//		if (iss >> StartStateIndex)
	//		{
	//			NewAutomaton->SetStartState(IndexMap[StartStateIndex]);
	//		}
	//	}

	//	OutLexer = new Lexer(NewAutomaton, NewTokenList);
	//	return true;
	//}

	bool Factory::Deserialize(DFA*& OutAutomaton, const std::string& InContent)
	{
		std::stringstream InStream(InContent);

		OutAutomaton = new DFA();

		std::string StartState; // Uses Index as Name
		InStream >> StartState;

		std::string Line;

		// Read State Line
		{
			std::getline(InStream, Line);
			std::string StateName;
			int StatePriority;
			std::istringstream iss(Line);
			while (iss >> StateName >> StatePriority)
			{
				OutAutomaton->CreateNewState(StateName, StatePriority);
			}

			//std::cout << "DFA States Loaded" << std::endl;

			// Mark Start State
			OutAutomaton->SetStartState(StartState);
			//std::cout << "DFA Start State Set" << std::endl;
		}

		// Read Transition Lines
		while (std::getline(InStream, Line))
		{
			std::istringstream iss(Line);

			// Read State Names
			std::string StartState;
			std::string EndState;
			std::set<char> Condition;
			iss >> StartState >> EndState;

			// Read Condition Symbols
			int symbol;
			while (iss >> symbol)
			{
				Condition.insert(char(symbol));
			}

			// Create Transition
			OutAutomaton->CreateNewTransition(StartState, EndState, Condition);
		}
		
		//std::cout << "Automaton States Connected" << std::endl;
		return true;
	}

}