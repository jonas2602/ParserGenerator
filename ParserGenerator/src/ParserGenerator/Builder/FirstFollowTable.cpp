#include "FirstFollowTable.h"
#include "../Utils/Math.h"
#include <iostream>

namespace ParserGenerator {

	FirstFollowSet::FirstFollowSet(bool InNullable, const std::set<std::string>& InFirstSet, const std::set<std::string>& InFollowSet)
		: m_bNullable(InNullable), m_FirstSet(InFirstSet), m_FollowSet(InFollowSet)
	{ }

	bool FirstFollowSet::MakeNullable()
	{
		if (!m_bNullable)
		{
			m_bNullable = true;
			return true;
		}

		return false;
	}

	bool FirstFollowSet::AddFistElement(const std::string& Element)
	{
		size_t PreSize = m_FirstSet.size();
		m_FirstSet.insert(Element);

		return PreSize < m_FirstSet.size();
	}

	bool FirstFollowSet::AddFistElement(const std::set<std::string>& Elements)
	{
		size_t PreSize = m_FirstSet.size();
		m_FirstSet.insert(Elements.begin(), Elements.end());

		return PreSize < m_FirstSet.size();
	}

	bool FirstFollowSet::AddFollowElement(const std::string& Element)
	{
		size_t PreSize = m_FollowSet.size();
		m_FollowSet.insert(Element);

		return PreSize < m_FollowSet.size();
	}

	bool FirstFollowSet::AddFollowElement(const std::set<std::string>& Elements)
	{
		size_t PreSize = m_FollowSet.size();
		m_FollowSet.insert(Elements.begin(), Elements.end());

		return PreSize < m_FollowSet.size();
	}

	FirstFollowTable::FirstFollowTable(ParserConfig* InConfig, Alphabet* InAlphabet)
		: m_Config(InConfig), m_Alphabet(InAlphabet)
	{
		FillFirstFollows();
	}

	FirstFollowTable::~FirstFollowTable()
	{

	}

	void FirstFollowTable::FillFirstFollows()
	{
		// Add Terminals with itself as only first and not nullable
		for (const std::string& Terminal : m_Alphabet->GetTerminalNames())
		{
			m_Data[Terminal] = FirstFollowSet(false, { Terminal }, {});
		}

		// Add NonTerminals not Nullable and with First/Follow Sets empty
		for (const std::string& NonTerminal : m_Alphabet->GetNonTerminalNames())
		{
			m_Data[NonTerminal] = FirstFollowSet(false, {}, {});
		}

		bool bChanged = true;
		while (bChanged)
		{
			bChanged = false;
			for (RuleDefinition* Production : m_Config->GetProductionList())
			{
				// Check if all Token Classes are nullable
				// by moving forward through the tokenstream
				bool bNewNullable = true;
				for (RuleElement* Element : Production->m_RuleElements)
				{
					// because all previous Tokens were Nullable, the current Token can be the first token of the current production
					if (m_Data[Production->m_NonTerminal].AddFistElement(m_Data[Element->m_Content].m_FirstSet))
					{
						bChanged = true;
					}

					// Is Epsilon? -> nullable
					if (PC::IsEpsilon(Element->m_Content))
					{
						continue;
					}

					// stop here if Element not Nullable
					if (!m_Data[Element->m_Content].m_bNullable)
					{
						bNewNullable = false;
						break;
					}
				}

				// Update "Nullability" of Map Entry if now nullable
				if (bNewNullable)
				{
					if (m_Data[Production->m_NonTerminal].MakeNullable())
					{
						bChanged = true;
					}
				}

				// look for following nullables
				// by mowing backwards through the token stream
				int LastNullable = Production->GetElementCount() - 1;
				for (int i = Production->GetElementCount() - 1; i >= 0; i--)
				{
					FirstFollowSet& TokenDataI = m_Data[Production->GetElementAtIndex(i)->m_Content];

					// Nullable from here to the end of the production?
					if (LastNullable == Production->GetElementCount() - 1)
					{
						// ... following of the current production can also follow the current token
						if (TokenDataI.AddFollowElement(m_Data[Production->m_NonTerminal].m_FollowSet))
						{
							bChanged = true;
						}
					}

					// Add first of all Tokens between self and the lastNullable (take care of "out of bounds")
					for (int j = i + 1; j < Math::Min(LastNullable + 2, Production->GetElementCount()); j++)
					{
						FirstFollowSet& TokenDataJ = m_Data[Production->GetElementAtIndex(j)->m_Content];
						if (TokenDataI.AddFollowElement(TokenDataJ.m_FirstSet))
						{
							bChanged = true;
						}
					}

					// self not nullable?
					if (!TokenDataI.m_bNullable)
					{
						// ... move last nullable to self - 1
						LastNullable = i - 1;
					}
				}
			}
		}
	}

	void FirstFollowTable::CreateParsingTable(PCT::ParsingTable* OutTable)
	{
		// Create Predictive Parsing Table
		for (const std::string& NonTerminal : m_Alphabet->GetNonTerminalNames())
		{
			for (RuleDefinition* Production : m_Config->GetAllProductionsForNonTerminal(NonTerminal))
			{
				// Get First Element of the current Production
				const std::string& StartToken = Production->GetElementAtIndex(0)->m_Content;
				if (m_Alphabet->IsRule(StartToken))
				{
					// If Element is Non Terminal ...
					// ... add all first elements of this nonterminal as reachable with the current production
					for (const std::string& First : m_Data[StartToken].m_FirstSet)
					{
						SetProduction(OutTable, NonTerminal, First, Production);
						//printf("NonTerminal First (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), First.c_str());
					}

					// ... and all follow elements if the nonterminal if it is nullable
					if (m_Data[StartToken].m_bNullable)
					{
						for (const std::string& Follow : m_Data[StartToken].m_FollowSet)
						{
							SetProduction(OutTable, NonTerminal, Follow, Production);
							//printf("NonTerminal Follow (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), Follow.c_str());
						}
					}
				}
				else if (PC::IsEpsilon(StartToken))
				{
					for (const std::string& Follow : m_Data[NonTerminal].m_FollowSet)
					{
						SetProduction(OutTable, NonTerminal, Follow, Production);
						//printf("Epsilon (%s, EPSILON) -> %s\n", NonTerminal.c_str(), Follow.c_str());
					}
				}
				else
				{
					SetProduction(OutTable, NonTerminal, StartToken, Production);
					//printf("Terminal (%s, %s) -> %s\n", NonTerminal.c_str(), StartToken.c_str(), StartToken.c_str());
				}
			}
		}
	}

	void FirstFollowTable::SetProduction(PCT::ParsingTable* OutTable, const std::string& NonTerminal, const std::string& Token, RuleDefinition* Production)
	{
		int TokenIndex = m_Alphabet->GetTokenIndex(Token);
		int NonTerminalIndex = m_Alphabet->GetRuleIndex(NonTerminal);
		int LocalProductionIndex = Production->m_LocalRuleIndex;

		if (!OutTable->SetProductionIndex(NonTerminalIndex, TokenIndex, LocalProductionIndex))
		{
			std::cout << "Table Element [NonTerminal(" << NonTerminal << "), Token(" << Token << ")] already set to '" << Production << "'. => Parser is ambiguous" << std::endl;
		}
	}
}