#include "Lexer.h"

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <set>

#include "Automaton/Factory.h"
#include "../ParserTypes.h"
#include "../Utils/Math.h"

namespace ParserCore {

	void LineTracker::Analyze(const std::string& InData)
	{
		for (const char& Symbol : InData)
		{
			if (Symbol == LF)
			{
				m_Line++;
				m_Column = 0;
			}
			else
			{
				m_Column++;
			}

			m_TotalCount++;
		}
	}

	Lexer::Lexer(const std::string& InSourceCode)
		: m_SourceCode(InSourceCode), m_DFA(nullptr)
	{
		// Call in inherited Constructor!!! because of c++ reasons^^
		//this->LoadAutomaton();
	}

	Lexer::~Lexer()
	{
		delete m_DFA;
	}

	void Lexer::Init()
	{
		//std::cout << "Init Lexer" << std::endl;

		m_HiddenTypes = GetHiddenTokenTypes();
		this->LoadAutomaton();
		//std::cout << "Automaton Loaded" << std::endl;
	}

	void Lexer::LoadAutomaton()
	{
		std::string AutomatonString = GetSerializedAutomaton();
		Automaton::Factory::Deserialize(m_DFA, AutomatonString);
	}

	bool Lexer::Tokenize(std::vector<Token*>& OutTokens)
	{
		std::string::iterator StartingPoint = m_SourceCode.begin();
		std::string::iterator SymbolIterator = m_SourceCode.begin();
		while (SymbolIterator < m_SourceCode.end())
		{
			std::string::iterator ConfirmedEnd;
			Automaton::State* LastFinalState = nullptr;
			Automaton::State* ActiveState = m_DFA->GetStartState();

			// Read Input while DEA has not reached a dead end
			while (ActiveState != nullptr)
			{
				// Override final state if new final state is reached
				if (ActiveState->IsFinalState())
				{
					ConfirmedEnd = SymbolIterator;
					LastFinalState = ActiveState;
				}

				// Perform Step in State Machine, break if no valid Transition available
				char ActiveSymbol = SymbolIterator == m_SourceCode.end() ? '\0' : *SymbolIterator++;
				ActiveState = m_DFA->Step(ActiveState, ActiveSymbol);
			}

			if (!LastFinalState)
			{
				int PreviewLength = Math::Min<int>(std::distance(StartingPoint, m_SourceCode.end()), m_MaxPreviewLength);
				std::string Preview(StartingPoint, StartingPoint + PreviewLength);
				std::cout << "Unable to find TokenType for: '" << Preview << "'... at [" << Tracker.GetLine() << "," << Tracker.GetColumn() + 1 << "]" << std::endl;
				return false;
			}


			int TokenType = LastFinalState->GetStatePriority();
			std::string FoundString = std::string(StartingPoint, ConfirmedEnd);
			if (IsVisibleToken(TokenType))
			{
				m_TokenStream.push_back(new Token(FoundString, TokenType, Tracker.GetLine(), Tracker.GetColumn() + 1));
			}
			Tracker.Analyze(FoundString);

			StartingPoint = ConfirmedEnd;
			SymbolIterator = ConfirmedEnd;
		}

		// Push EOF Token to the End
		m_TokenStream.push_back(Token::EOS_TOKEN);
		OutTokens = m_TokenStream;
		return true;
	}

	//void Lexer::CreateToken()
	//{
	//	//if (m_HiddenTypes.find(LastPriority) == m_HiddenTypes.end())
	//	//{
	//	//	std::string FoundString = m_SourceCode.substr(StartingPoint, ConfirmedLength);
	//	//	int LineNumber = 0; // (int)std::count(m_SourceCode.begin(), m_SourceCode.begin() + StartingPoint, RegExp::LF);
	//	//	int ColumnNumber = 0;
	//	//	m_TokenStream.push_back(new Token(FoundString, LastPriority, LineNumber, ColumnNumber));
	//	//}

	//	//StartingPoint += ConfirmedLength;
	//	//ActiveSymbolIndex = StartingPoint;
	//}

	//bool Lexer::ValidateActiveState()
	//{
	//	return false;
	//}

	//bool Lexer::TryStepAutomaton()
	//{
	//	// Perform Step in State Machine, break if no valid Transition available
	//	const char& ActiveSymbol = *m_SymbolIterator;
	//	m_ActiveState = m_DFA->Step(m_ActiveState, ActiveSymbol);
	//	if (!m_ActiveState)
	//	{
	//		return false;
	//	}

	//	if (ActiveSymbol == LF)
	//	{
	//		EnhancedLineCounter++;
	//		EnhancedCharCount = 0;
	//	}
	//	EnhancedTotalCounter++;

	//	// Move to next Symbol in String
	//	m_SymbolIterator++;

	//	//// Override final state if new final state is reached
	//	//int StatePriority = ActiveState->GetStatePriority();
	//	//if (StatePriority > -1)
	//	//{
	//	//	ConfirmedLength = ActiveSymbolIndex - StartingPoint;
	//	//	LastPriority = StatePriority;
	//	//}
	//	return true;
	//}

	//void Lexer::Fallback()
	//{
	//	m_StartSymbol += m_ConfirmedTokenLength;
	//	m_SymbolIterator = m_StartSymbol;
	//	m_ActiveState = m_DFA->GetStartState();
	//}

	//void Lexer::FindFinalState()
	//{
	//	int LinesPassed = 0;
	//	//int 
	//}
}