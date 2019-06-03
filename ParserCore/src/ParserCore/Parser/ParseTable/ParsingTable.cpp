#include "ParsingTable.h"
#include <iostream>

namespace ParserCore::ParseTable {
	
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