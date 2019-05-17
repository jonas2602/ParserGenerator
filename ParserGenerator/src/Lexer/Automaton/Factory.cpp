#include "Factory.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace ParserGenerator::Automaton {

	bool Factory::Serialize(DFA* Automaton, const std::string& FilePath)
	{
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		std::map<State*, int> IndexMap;

		// TODO: TokenName, TokenIndex, bSkip

		// Create Output Streams
		int Index = 0;
		for (const std::pair<std::string, State*>& Element : Automaton->m_StateMap)
		{
			// Write State Data
			State* ActiveState = Element.second;
			int StateIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = Index++;
			StateStream << StateIndex << " " << ActiveState->GetName() << " " << ActiveState->GetStatePriority() << std::endl;

			// Write Transition Data
			for (Transition* Trans : ActiveState->GetTransitions())
			{
				State* OtherState = Trans->GetTargetState();
				int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = Index++;
				TransitionStream << StateIndex << " " << OtherIndex;

				// Write Condition Data
				for (const char& Symbol : Trans->GetCondition())
				{
					TransitionStream << " " << (int)Symbol;
				}

				TransitionStream << std::endl;
			}
		}

		// Write to File
		std::ofstream File(FilePath);
		File << StateStream.str();
		File << std::endl;
		File << TransitionStream.str();

		return true;
	}

	bool Factory::Deserialize(DFA* OutAutomaton, const std::string& FilePath)
	{
		std::ifstream File(FilePath);
		if (!File) {
			std::cout << "Unable to open file: " << FilePath << std::endl;
			return false;
		}

		std::string Line;

		// Read State Lines
		while (std::getline(File, Line))
		{
			std::istringstream iss(Line);
			std::string StateName;
			int StatePriority;
			if (!(iss >> StateName >> StatePriority))
			{
				// Reached End of State List
				break;
			}

			OutAutomaton->CreateNewState(StateName, StatePriority);
		}

		// Read all other Lines (Transitions)
		while (std::getline(File, Line))
		{
			std::istringstream iss(Line);
			std::string StartState;
			std::string EndState;
			std::set<char> Condition;
			if (!(iss >> StartState >> EndState))
			{
				// Reached End of Transition List
				break;
			}

			char symbol;
			while (iss >> symbol)
			{
				Condition.insert(symbol);
			}

			OutAutomaton->CreateNewTransition(StartState, EndState, Condition);
		}

		return true;
	}

}