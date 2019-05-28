#include "Lexer.h"

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <set>

#include "Automaton/Factory.h"

namespace ParserGenerator {

	//Lexer::Lexer(LexerConfig* InConfig)
	//{
	//	// Create Empty Automatons
	//	Automaton::NFA* TempNFA = new Automaton::NFA();
	//	m_DFA = new Automaton::DFA();

	//	// Add all regex to "simple" NFA
	//	int Priority = 0;
	//	for (const LexerConfigElement& Regex : InConfig->GetRegexList())
	//	{
	//		std::cout << "Added " << Regex.m_Name << " with Priority of " << Priority << std::endl;
	//		Regex.m_Expression->Parse(TempNFA, Regex.m_Name, Priority++);
	//	}

	//	// Create combined DFA
	//	TempNFA->CreateDFA(m_DFA);
	//	delete TempNFA;

	//	m_TokenTypes = InConfig->GetRegexList();
	//}

	//Lexer::Lexer(Automaton::DFA* InDFA, const std::vector<LexerConfigElement>& InTokenTypes)
	//	: m_DFA(InDFA), m_TokenTypes(InTokenTypes)
	//{

	//}

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
		std::cout << "Init Lexer" << std::endl;

		m_HiddenTypes = GetHiddenTokenTypes();
		this->LoadAutomaton();
		std::cout << "Automaton Loaded" << std::endl;

		Tokenize();
		std::cout << "Input Tokenized" << std::endl;
	}

	void Lexer::LoadAutomaton()
	{
		std::string AutomatonString = GetSerializedAutomaton();
		Automaton::Factory::Deserialize(m_DFA, AutomatonString);
	}

	void Lexer::Tokenize()
	{
		int StartingPoint = 0;
		int ActiveSymbolIndex = 0;
		while (ActiveSymbolIndex < m_SourceCode.size())
		{
			int ConfirmedLength = 0;
			int LastPriority = -1;
			Automaton::State* ActiveState = m_DFA->GetStartState();

			// Read Input while DEA has not reached a dead end
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
				const char& ActiveSymbol = m_SourceCode[ActiveSymbolIndex];
				ActiveState = m_DFA->Step(ActiveState, ActiveSymbol);
				if (ActiveState)
				{
					// Move to next Symbol in String
					ActiveSymbolIndex += 1;
				}
			}

			if (ConfirmedLength == 0)
			{
				std::cout << "Unable to find Rule for: '" << m_SourceCode.substr(StartingPoint) << "'" << std::endl;
				break;
			}

			//const LexerConfigElement& ConfigElement = m_TokenTypes[LastPriority];
			//switch (ConfigElement.m_Action)
			//{
			//case ELexerAction::DEFAULT:
			if (m_HiddenTypes.find(LastPriority) == m_HiddenTypes.end())
			{
				std::string FoundString = m_SourceCode.substr(StartingPoint, ConfirmedLength);
				int LineNumber = (int)std::count(m_SourceCode.begin(), m_SourceCode.begin() + StartingPoint, RegExp::LF);
				int ColumnNumber = 0;
				m_TokenStream.push_back(new Token(FoundString, LastPriority, LineNumber, ColumnNumber));
				//	break;
			}
			//case ELexerAction::SKIP:
			//{
			//	// Nothing to do here ...
			//	break;
			//}
			//}

			StartingPoint += ConfirmedLength;
			ActiveSymbolIndex = StartingPoint;
		}

		// Push EOF Token to the End
		m_TokenStream.push_back(Token::EOS_TOKEN);
	}
}