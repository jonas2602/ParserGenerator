#include "TableFactory.h"

#include <sstream>
#include <fstream>
#include <iostream>



namespace ParserCore::ParseTable {

	bool TableFactory::Deserialize(ParsingTable*& OutTable, const std::string& InContent)
	{
		// NonTerminal -> [Token -> Rule]
		std::map<int, std::map<int, int>> PredictionMap;

		std::istringstream iss(InContent);
		int NonTerminalIndex;
		int TokenIndex;
		int RuleIndex;
		while (iss >> NonTerminalIndex >> TokenIndex >> RuleIndex)
		{
			PredictionMap[NonTerminalIndex][TokenIndex] = RuleIndex;
		}

		OutTable = new ParsingTable(PredictionMap);
		return true;
	}

}