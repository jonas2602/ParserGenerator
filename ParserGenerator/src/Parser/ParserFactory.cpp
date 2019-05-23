#include "ParserFactory.h"

#include <sstream>
#include <fstream>
#include <iostream>



namespace ParserGenerator {
	//bool ParserFactory::Serialize(ParsingTable* InTable, Alphabet* InAlphabet, const std::string& FilePath)
	//{
	//	// Create Output Streams
	//	std::stringstream TerminalStream;
	//	std::stringstream NonTerminalStream;
	//	std::stringstream TableStream;
	//	std::stringstream RuleStream;

	//	// Write List of Terminals
	//	ParserConfig* Config = InTable->GetParserConfig();
	//	std::map<std::string, int> TerminalMap;
	//	int TerminalIndex = 0;
	//	for (const std::string& Terminal : Config->GetTerminals())
	//	{
	//		TerminalMap[Terminal] = TerminalIndex;
	//		TerminalStream << TerminalIndex++ << " " << Terminal << std::endl;
	//	}

	//	// Write List of NonTerminals
	//	int NonTerminalIndex = 0;
	//	std::map<std::string, int> NonTerminalMap;
	//	for (const std::string& NonTerminal : Config->GetNonTerminals())
	//	{
	//		NonTerminalMap[NonTerminal] = NonTerminalIndex;
	//		NonTerminalStream << NonTerminalIndex++ << " " << NonTerminal << std::endl;
	//	}

	//	std::map<std::string, int> NonTerminalCountMap;
	//	std::map<ParserConfigElement*, int> ProductionMap;

	//	// Write Rules
	//	for (ParserConfigElement* Production : Config->GetProductionList())
	//	{
	//		int ProductionIndex = NonTerminalCountMap[Production->m_NonTerminal];
	//		NonTerminalCountMap[Production->m_NonTerminal] = ProductionIndex + 1;
	//		ProductionMap[Production] = ProductionIndex;

	//		RuleStream << ProductionIndex << " " << Production->m_NonTerminal << " ->";
	//		for (const std::string& TokenClass : Production->m_TokenClasses)
	//		{
	//			RuleStream << " " << TokenClass;
	//		}

	//		RuleStream << std::endl;
	//	}

	//	// Write ParseTable
	//	for (const std::pair<std::string, std::map<std::string, ParserConfigElement*>>& NonTerminalPair : InTable->GetProductionMap())
	//	{
	//		for (const std::pair<std::string, ParserConfigElement*>& TerminalPair : NonTerminalPair.second)
	//		{
	//			TableStream << NonTerminalMap[NonTerminalPair.first] << " " << TerminalMap[TerminalPair.first] << " " << ProductionMap[TerminalPair.second] << std::endl;
	//		}
	//	}


	//	// Write to File
	//	std::ofstream File(FilePath);
	//	if (!File.is_open())
	//	{
	//		std::cout << "Failed to open File " << FilePath << std::endl;
	//		return false;
	//	}

	//	File << TerminalStream.str();
	//	File << std::endl;
	//	File << NonTerminalStream.str();
	//	File << std::endl;
	//	File << TableStream.str();
	//	File << std::endl;
	//	File << RuleStream.str();

	//	return true;
	//}

	//bool ParserFactory::Serialize(Parser* InParser, const std::string& FilePath)
	//{
	//	// Create Output Streams
	//	std::stringstream TerminalStream;
	//	std::stringstream NonTerminalStream;
	//	std::stringstream TableStream;
	//	std::stringstream RuleStream;

	//	// Write List of Terminals
	//	ParserConfig* Config = nullptr; // InParser->GetParserConfig();
	//	std::map<std::string, int> TerminalMap;
	//	int TerminalIndex = 0;
	//	for (const std::string& Terminal : Config->GetTerminals())
	//	{
	//		TerminalMap[Terminal] = TerminalIndex;
	//		TerminalStream << TerminalIndex++ << " " << Terminal << std::endl;
	//	}

	//	// Write List of NonTerminals
	//	int NonTerminalIndex = 0;
	//	std::map<std::string, int> NonTerminalMap;
	//	for (const std::string& NonTerminal : Config->GetNonTerminals())
	//	{
	//		NonTerminalMap[NonTerminal] = NonTerminalIndex;
	//		NonTerminalStream << NonTerminalIndex++ << " " << NonTerminal << std::endl;
	//	}

	//	std::map<std::string, int> NonTerminalCountMap;
	//	std::map<ParserConfigElement*, int> ProductionMap;

	//	// Write Rules
	//	for (ParserConfigElement* Production : Config->GetProductionList())
	//	{
	//		int ProductionIndex = NonTerminalCountMap[Production->m_NonTerminal];
	//		NonTerminalCountMap[Production->m_NonTerminal] = ProductionIndex + 1;
	//		ProductionMap[Production] = ProductionIndex;

	//		RuleStream << ProductionIndex << " " << Production->m_NonTerminal << " ->";
	//		for (const std::string& TokenClass : Production->m_TokenClasses)
	//		{
	//			RuleStream << " " << TokenClass;
	//		}

	//		RuleStream << std::endl;
	//	}

	//	// Write ParseTable
	//	ParsingTable* Table = InParser->GetParsingTable();
	//	for (const std::pair<std::string, std::map<std::string, ParserConfigElement*>>& NonTerminalPair : Table->GetProductionMap())
	//	{
	//		for (const std::pair<std::string, ParserConfigElement*>& TerminalPair : NonTerminalPair.second)
	//		{
	//			TableStream << NonTerminalMap[NonTerminalPair.first] << " " << TerminalMap[TerminalPair.first] << " " << ProductionMap[TerminalPair.second] << std::endl;
	//		}
	//	}


	//	// Write to File
	//	std::ofstream File(FilePath);
	//	if (!File.is_open())
	//	{
	//		std::cout << "Failed to open File " << FilePath << std::endl;
	//		return false;
	//	}

	//	File << TerminalStream.str();
	//	File << std::endl;
	//	File << NonTerminalStream.str();
	//	File << std::endl;
	//	File << TableStream.str();
	//	File << std::endl;
	//	File << RuleStream.str();

	//	return true;
	//}

	//bool ParserFactory::Deserialize(Parser*& OutParser, const std::string& FilePath)
	//{
	//	std::ifstream File(FilePath);
	//	if (!File) {
	//		std::cout << "Unable to open file: " << FilePath << std::endl;
	//		return false;
	//	}

	//	std::string Line;

	//	std::map<int, std::string> TerminalMap;
	//	std::map<int, std::string> NonTerminalMap;

	//	// Read Terminals
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int TerminalIndex;
	//		std::string TerminalName;
	//		if (!(iss >> TerminalIndex >> TerminalName))
	//		{
	//			// Reached End of Token List
	//			break;
	//		}

	//		TerminalMap[TerminalIndex] = TerminalName;
	//	}

	//	// Read NonTerminals
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int NonTerminalIndex;
	//		std::string NonTerminalName;
	//		if (!(iss >> NonTerminalIndex >> NonTerminalName))
	//		{
	//			// Reached End of Token List
	//			break;
	//		}

	//		NonTerminalMap[NonTerminalIndex] = NonTerminalName;
	//	}

	//	// Read Table Entries
	//	while (std::getline(File, Line))
	//	{
	//		std::istringstream iss(Line);
	//		int NonTerminalIndex;
	//		int TerminalIndex;
	//		std::string RuleIndex;
	//		if (!(iss >> NonTerminalIndex >> TerminalIndex >> RuleIndex))
	//		{
	//			// Reached End of Token List
	//			break;
	//		}

	//		//NonTerminalMap[NonTerminalIndex] = NonTerminalName;
	//	}

	//	return true;
	//}

	bool ParserFactory::Deserialize(ParsingTable*& OutTable, const std::string& InContent)
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