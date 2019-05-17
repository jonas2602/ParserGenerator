#include "Lexer.h"

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <set>

#include "Automaton/Factory.h"

namespace ParserGenerator {

	Lexer::Lexer(LexerConfig* InConfig)
		: m_Config(InConfig)
	{
		// Create Empty Automatons
		m_NFA = new Automaton::NFA();
		m_DFA = new Automaton::DFA();

		// Add all regex to "simple" NFA
		int Priority = 0;
		for (const LexerConfigElement& Regex : InConfig->GetRegexList())
		{
			std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
			Regex.m_Expression->Parse(m_NFA, Regex.m_Name, Priority++);
		}

		// Create combined DFA
		m_NFA->CreateDFA(m_DFA);
	}


	Lexer::~Lexer()
	{
		delete m_DFA;
		delete m_NFA;
	}

	std::vector<Token*> Lexer::Tokenize(const std::string& SourceCode) const
	{
		std::vector<Token*> TokenList;

		int StartingPoint = 0;
		int ActiveSymbolIndex = 0;
		while (ActiveSymbolIndex < SourceCode.size())
		{
			int ConfirmedLength = 0;
			int LastPriority = -1;
			Automaton::State* ActiveState = m_DFA->GetStartState();

			// Read Input while dea has not reached a dead end
			while (ActiveState != nullptr)
			{
				// Override final state if new final state is reached
				int StatePriority = ActiveState->GetStatePriority();
				if (StatePriority > -1)
				{
					ConfirmedLength = ActiveSymbolIndex - StartingPoint;
					LastPriority = StatePriority;
				}

				// Perform Step in State Machine, break if no valid Transition available
				const char& ActiveSymbol = SourceCode[ActiveSymbolIndex];
				ActiveState = m_DFA->Step(ActiveState, ActiveSymbol);
				if (ActiveState)
				{
					// Move to next Symbol in String
					ActiveSymbolIndex += 1;
				}
			}

			if (ConfirmedLength == 0)
			{
				std::cout << "Unable to find Rule for: '" << SourceCode.substr(StartingPoint) << "'" << std::endl;
				break;
			}

			const LexerConfigElement& ConfigElement = m_Config->GetConfigElementByIndex(LastPriority);
			switch (ConfigElement.m_Action)
			{
				case ELexerAction::DEFAULT:
				{
					std::string FoundString = SourceCode.substr(StartingPoint, ConfirmedLength);
					int LineNumber = (int)std::count(SourceCode.begin(), SourceCode.begin() + StartingPoint, RegExp::LF);
					int ColumnNumber = 0;
					TokenList.push_back(new Token(FoundString, ConfigElement.m_Name, LastPriority, LineNumber, ColumnNumber));
					break;
				}
				case ELexerAction::SKIP:
				{
					// Nothing to do here ...
					break;
				}
			}

			StartingPoint += ConfirmedLength;
			ActiveSymbolIndex = StartingPoint;
		}

		return TokenList;
	}

	bool Lexer::Serialize(const std::string& FilePath) const
	{
		return Automaton::Factory::Serialize(m_DFA, FilePath);
	}


}