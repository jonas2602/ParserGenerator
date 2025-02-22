#include "ParsingTable.h"
#include "../../Utils/Math.h"
//#include "../Lexer/Token.h"
#include <iostream>

namespace ParserCore::ParseTable {

	//FirstFollowSet::FirstFollowSet(bool InNullable, const std::set<std::string>& InFirstSet, const std::set<std::string>& InFollowSet)
	//	: m_bNullable(InNullable), m_FirstSet(InFirstSet), m_FollowSet(InFollowSet)
	//{ }

	//bool FirstFollowSet::MakeNullable()
	//{
	//	if (!m_bNullable)
	//	{
	//		m_bNullable = true;
	//		return true;
	//	}

	//	return false;
	//}

	//bool FirstFollowSet::AddFistElement(const std::string& Element)
	//{
	//	size_t PreSize = m_FirstSet.size();
	//	m_FirstSet.insert(Element);

	//	return PreSize < m_FirstSet.size();
	//}

	//bool FirstFollowSet::AddFistElement(const std::set<std::string>& Elements)
	//{
	//	size_t PreSize = m_FirstSet.size();
	//	m_FirstSet.insert(Elements.begin(), Elements.end());

	//	return PreSize < m_FirstSet.size();
	//}

	//bool FirstFollowSet::AddFollowElement(const std::string& Element)
	//{
	//	size_t PreSize = m_FollowSet.size();
	//	m_FollowSet.insert(Element);

	//	return PreSize < m_FollowSet.size();
	//}

	//bool FirstFollowSet::AddFollowElement(const std::set<std::string>& Elements)
	//{
	//	size_t PreSize = m_FollowSet.size();
	//	m_FollowSet.insert(Elements.begin(), Elements.end());

	//	return PreSize < m_FollowSet.size();
	//}

	//ParsingTable::ParsingTable(ParserConfig* InConfig)
	//	: m_Config(InConfig)
	//{
	//	// Calculate temporary nullable, first, follow
	//	std::map<std::string, FirstFollowSet> FirstFollowMap;
	//	CreateFirstFollowTable(FirstFollowMap);

	//	/*for (const std::string& NonTerminal : m_Config->GetNonTerminals())
	//	{
	//		const FirstFollowSet& FFSet = FirstFollowMap[NonTerminal];

	//		std::cout << NonTerminal << " -> NULLABLE: " << FFSet.m_bNullable << " FIRST: {";

	//		for (const std::string& First : FFSet.m_FirstSet)
	//		{
	//			std::cout << " " << First;
	//		}

	//		std::cout << " }, FOLLOW: {";


	//		for (const std::string& Follow : FFSet.m_FollowSet)
	//		{
	//			std::cout << " " << Follow;
	//		}

	//		std::cout << " }" << std::endl;
	//	}*/

	//	// Fill Actual Table that is used for parsing
	//	FillPredictionTable(FirstFollowMap);
	//}

	ParsingTable::ParsingTable()
	{

	}

	ParsingTable::ParsingTable(const std::map<int, std::map<int, int>>& InPredictionMap)
		: m_PredictionMap(InPredictionMap)
	{
	}

	ParsingTable::~ParsingTable()
	{

	}

	//void ParsingTable::CreateFirstFollowTable(std::map<std::string, FirstFollowSet>& OutFirstFollowMap) const
	//{
	//	// Add Terminals with itself as only first and not nullable
	//	for (const std::string& Terminal : m_Config->GetTerminals())
	//	{
	//		OutFirstFollowMap[Terminal] = FirstFollowSet(false, { Terminal }, {});
	//	}

	//	// Add NonTerminals not Nullable and with First/Follow Sets empty
	//	for (const std::string& NonTerminal : m_Config->GetNonTerminals())
	//	{
	//		OutFirstFollowMap[NonTerminal] = FirstFollowSet(false, {}, {});
	//	}

	//	// Add End of Stream Token to the Start Production
	//	OutFirstFollowMap[m_Config->GetStartNonTerminal()].AddFollowElement(Token::EOS);

	//	bool bChanged = true;
	//	while (bChanged)
	//	{
	//		bChanged = false;
	//		for (ParserConfigElement* Production : m_Config->GetProductionList())
	//		{
	//			// Check if all Token Classes are nullable
	//			// by moving forward through the tokenstream
	//			bool bNewNullable = true;
	//			for (const std::string& Token : Production->m_TokenClasses)
	//			{
	//				// because all previous Tokens were Nullable, the current Token can be the first token of the current production
	//				if (OutFirstFollowMap[Production->m_NonTerminal].AddFistElement(OutFirstFollowMap[Token].m_FirstSet))
	//				{
	//					bChanged = true;
	//				}

	//				// Is Epsilon? -> nullable
	//				if (StateMachine::IsEpsilon(Token))
	//				{
	//					continue;
	//				}

	//				// Is Map Element Nullable?
	//				if (!OutFirstFollowMap[Token].m_bNullable)
	//				{
	//					bNewNullable = false;
	//					break;
	//				}
	//			}
	//			// Update "Nullability" of Map Entry if now nullable
	//			if (bNewNullable)
	//			{
	//				if (OutFirstFollowMap[Production->m_NonTerminal].MakeNullable())
	//				{
	//					bChanged = true;
	//				}
	//			}

	//			// look for following nullables
	//			// by mowing backwards through the token stream
	//			int LastNullable = Production->GetTokenCount() - 1;
	//			for (int i = Production->GetTokenCount() - 1; i >= 0; i--)
	//			{
	//				FirstFollowSet& TokenDataI = OutFirstFollowMap[Production->GetTokenClassAtIndex(i)];

	//				// Nullable from here to the end of the production?
	//				if (LastNullable == Production->GetTokenCount() - 1)
	//				{
	//					// ... following of the current production can also follow the current token
	//					if (TokenDataI.AddFollowElement(OutFirstFollowMap[Production->m_NonTerminal].m_FollowSet))
	//					{
	//						bChanged = true;
	//					}
	//				}

	//				// Add first of all Tokens between self and the lastNullable (take care of "out of bounds")
	//				for (int j = i + 1; j < Math::Min(LastNullable + 2, Production->GetTokenCount()); j++)
	//				{
	//					FirstFollowSet& TokenDataJ = OutFirstFollowMap[Production->GetTokenClassAtIndex(j)];
	//					if (TokenDataI.AddFollowElement(TokenDataJ.m_FirstSet))
	//					{
	//						bChanged = true;
	//					}
	//				}

	//				// self not nullable?
	//				if (!TokenDataI.m_bNullable)
	//				{
	//					// ... move last nullable to self - 1
	//					LastNullable = i - 1;
	//				}
	//			}
	//		}
	//	}
	//}

	//void ParsingTable::FillPredictionTable(std::map<std::string, FirstFollowSet>& FirstFollowMap)
	//{
	//	// Create Predictive Parsing Table
	//	for (const std::string& NonTerminal : m_Config->GetNonTerminals())
	//	{
	//		for (ParserConfigElement* Production : m_Config->GetAllProductionsForNonTerminal(NonTerminal))
	//		{
	//			// Get First Element of the current Production
	//			const std::string& StartToken = Production->GetTokenClassAtIndex(0);
	//			if (m_Config->IsNonTerminal(StartToken))
	//			{
	//				// If Element is Non Terminal ...
	//				// ... add all first elements of this nonterminal as reachable with the current production
	//				for (const std::string& First : FirstFollowMap[StartToken].m_FirstSet)
	//				{
	//					SetProduction(NonTerminal, First, Production);
	//					//printf("NonTerminal First (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), First.c_str());
	//				}

	//				// ... and all follow elements if the nonterminal if it is nullable
	//				if (FirstFollowMap[StartToken].m_bNullable)
	//				{
	//					for (const std::string& Follow : FirstFollowMap[StartToken].m_FollowSet)
	//					{
	//						SetProduction(NonTerminal, Follow, Production);
	//						//printf("NonTerminal Follow (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), Follow.c_str());
	//					}
	//				}
	//			}
	//			else if (StateMachine::IsEpsilon(StartToken))
	//			{
	//				for (const std::string& Follow : FirstFollowMap[NonTerminal].m_FollowSet)
	//				{
	//					SetProduction(NonTerminal, Follow, Production);
	//					//printf("Epsilon (%s, EPSILON) -> %s\n", NonTerminal.c_str(), Follow.c_str());
	//				}
	//			}
	//			else
	//			{
	//				SetProduction(NonTerminal, StartToken, Production);
	//				//printf("Terminal (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), StartToken.c_str());
	//			}
	//		}
	//	}
	//}

	//void ParsingTable::SetProduction(const std::string& NonTerminal, const std::string& Token, ParserConfigElement* Production)
	//{
	//	if (m_PredictionMap[NonTerminal][Token])
	//	{
	//		std::cout << "Prediction Table Element (" << NonTerminal << ", " << Token << ") already set. Therefore the ParseTree would be ambiguous." << std::endl;
	//	}

	//	m_PredictionMap[NonTerminal][Token] = Production;
	//}

	//ParserConfigElement* ParsingTable::GetProduction(const std::string& NonTerminal, const std::string& Token)
	//{
	//	return m_PredictionMap[NonTerminal][Token];
	//}

	int ParsingTable::GetProductionIndex(int NonTerminal, int Token)
	{
		return m_PredictionMap[NonTerminal][Token];
	}

	bool ParsingTable::SetProductionIndex(int NonTerminal, int Token, int LocalRuleIndex)
	{
		if (m_PredictionMap[NonTerminal].find(Token) != m_PredictionMap[NonTerminal].end())
		{
			return false;
		}

		m_PredictionMap[NonTerminal][Token] = LocalRuleIndex;
		return true;
	}

}