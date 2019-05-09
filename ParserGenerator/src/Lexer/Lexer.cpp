#include "Lexer.h"

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <set>


Lexer::Lexer(LexerConfig* InConfig)
	: m_Config(InConfig)
{
	// Add all regex to "simple" NFA
	int Priority = 0;
	for (const LexerConfigElement& Regex : InConfig->GetRegexList())
	{
		std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
		Regex.m_Expression->Parse(m_NFA, Regex.m_Name, Priority++);
	}

	// Create combined DFA
	m_NFA.CreateDeterministic(m_DFA);
}


Lexer::~Lexer()
{
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
		State* ActiveState = *m_DFA.GetStartStates().begin();

		while (ActiveState != nullptr)
		{
			// Override final state if priority is higher or equal last final state
			int StatePriority = ActiveState->GetStatePriority();
			if (StatePriority >= 0 && StatePriority >= LastPriority)
			{
				ConfirmedLength = ActiveSymbolIndex - StartingPoint;
				LastPriority = StatePriority;
			}

			// Perform Step in State Machine, break if no valid Transition available
			const char& ActiveSymbol = SourceCode[ActiveSymbolIndex];
			std::set<State*> SymbolStep = ActiveState->Step(ActiveSymbol);
			if (SymbolStep.size() > 0)
			{
				ActiveSymbolIndex += 1;
				ActiveState = *SymbolStep.begin();
			}
			else
			{
				ActiveState = nullptr;
			}
		}

		if (ConfirmedLength == 0)
		{
			std::cout << "Unable to find Rule for " << SourceCode.substr(StartingPoint) << std::endl;
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
