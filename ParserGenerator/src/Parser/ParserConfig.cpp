#include "ParserConfig.h"

#include <iostream>
#include "../ParserTypes.h"

namespace ParserGenerator {



	ParserConfig::ParserConfig()
	{
	}


	ParserConfig::~ParserConfig()
	{
	}

	void ParserConfig::AddProduction(const std::string& NonTerminal, const std::vector<std::string>& TokenClasses)
	{
		m_NonTerminals.insert(NonTerminal);
		int& RuleCount = m_RuleCountMap[NonTerminal];
		m_ProductionList.push_back(new ParserConfigElement(NonTerminal, TokenClasses, RuleCount++));
	}

	void ParserConfig::FillTerminals()
	{
		for (ParserConfigElement* Production : m_ProductionList)
		{
			for (const std::string& Token : Production->m_TokenClasses)
			{
				if (!IsNonTerminal(Token) && !IsEpsilon(Token))
				{
					m_Terminals.insert(Token);
				}

			}
		}
	}

	bool ParserConfig::Validate(const std::set<std::string>& TerminalList)
	{
		// Fill TerminalList
		/*m_Terminals = TerminalList;

		for (ParserConfigElement* Production : m_ProductionList)
		{
			for (const std::string& Token : Production->m_TokenClasses)
			{
				if (!IsNonTerminal(Token) && !IsEpsilon(Token))
				{
					m_Terminals.insert(Token);
				}

			}
		}*/

		return true;
	}

	void ParserConfig::Normalize()
	{
		std::vector<ParserConfigElement*> NewRuleList;
		std::set<std::string> NewNonTerminalSet(m_NonTerminals);

		// Eliminate Left Recursion
		for (const std::string& NonTerminal : GetNonTerminals())
		{
			std::set<std::vector<std::string>> AlphaList;
			std::set<std::vector<std::string>> GammaList;

			// Divide rules in Sets of Alphas and Gammas
			const std::vector<ParserConfigElement*>& ElementRuleList = GetAllProductionsForNonTerminal(NonTerminal);
			for (ParserConfigElement* ConfigElement : ElementRuleList)
			{
				if (ConfigElement->m_TokenClasses[0] == NonTerminal)
				{
					GammaList.insert(std::vector<std::string>(ConfigElement->m_TokenClasses.begin() + 1, ConfigElement->m_TokenClasses.end()));
				}
				else
				{
					AlphaList.insert(ConfigElement->m_TokenClasses);
				}
			}

			// Has Rules that result in left recursion?
			if (GammaList.size() > 0)
			{
				// ... change them
				std::string NewNonTerminal = NonTerminal + "'";
				NewNonTerminalSet.insert(NewNonTerminal);

				// Handle Alphas
				for (const std::vector<std::string>& AlphaElement : AlphaList)
				{
					std::vector<std::string> NewTokenList(AlphaElement);
					NewTokenList.push_back(NewNonTerminal);
					ParserConfigElement* NewElement = new ParserConfigElement(NonTerminal, NewTokenList, 0);
					NewRuleList.push_back(NewElement);
				}

				// Handle Gammas
				for (const std::vector<std::string>& GammaElement : GammaList)
				{
					std::vector<std::string> NewTokenList(GammaElement);
					NewTokenList.push_back(NewNonTerminal);
					ParserConfigElement* NewElement = new ParserConfigElement(NewNonTerminal, NewTokenList, 0);
					NewRuleList.push_back(NewElement);
				}

				// Add Epsilon Rule
				ParserConfigElement* EpsilonProduction = new ParserConfigElement(NewNonTerminal, { EPSILON_S }, 0);
				NewRuleList.push_back(EpsilonProduction);
			}
			else
			{
				// ... use them as they are
				NewRuleList.insert(NewRuleList.end(), ElementRuleList.begin(), ElementRuleList.end());
			}
		}

		m_ProductionList = NewRuleList;
		m_NonTerminals = NewNonTerminalSet;

		// Eliminate Left Factoring
		for (const std::string& NonTerminal : GetNonTerminals())
		{
			std::set<std::string> FirstList;

			// Divide rules in Sets of Alphas and Gammas
			const std::vector<ParserConfigElement*>& ElementRuleList = GetAllProductionsForNonTerminal(NonTerminal);
			for (ParserConfigElement* Rule : ElementRuleList)
			{
				const std::string& First = Rule->GetTokenClassAtIndex(0);
				if (FirstList.find(First) != FirstList.end())
				{
					std::cout << "Detected Left Factoring in " << NonTerminal << " with start symbol " << First << std::endl;
				}

				FirstList.insert(First);
			}
		}
	}

	std::vector<ParserConfigElement*> ParserConfig::GetAllProductionsForNonTerminal(const std::string& NonTerminal) const
	{
		std::vector<ParserConfigElement*> OutRules;
		for (ParserConfigElement* Element : m_ProductionList)
		{
			if (Element->m_NonTerminal == NonTerminal)
			{
				OutRules.push_back(Element);
			}
		}

		return OutRules;
	}

	const std::vector<std::string>& ParserConfig::GetRuleElements(const std::string& NonTerminalName, int LocalRuleIndex)
	{
		for (ParserConfigElement* Element : m_ProductionList)
		{
			if (Element->m_LocalRuleIndex == LocalRuleIndex && Element->m_NonTerminal == NonTerminalName)
			{
				return Element->m_TokenClasses;
			}
		}

		return std::vector<std::string>();
	}

	bool ParserConfig::IsNonTerminal(const std::string& Token) const
	{
		return m_NonTerminals.find(Token) != m_NonTerminals.end();
	}

	std::map<std::string, int> ParserConfig::GetNonTerminalMap() const
	{
		std::map<std::string, int> NonTerminalMap;

		int Index = 0;
		for (const std::string& NonTerminal : m_NonTerminals)
		{
			NonTerminalMap[NonTerminal] = Index++;
		}

		return NonTerminalMap;
	}

}