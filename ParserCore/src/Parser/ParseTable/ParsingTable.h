#pragma once

#include <map>
#include "../../Core.h"

namespace ParserCore::ParseTable {

	//struct FirstFollowSet
	//{
	//	bool m_bNullable;
	//	std::set<std::string> m_FirstSet;
	//	std::set<std::string> m_FollowSet;

	//	FirstFollowSet(bool InNullable = false, const std::set<std::string>& InFirstSet = {}, const std::set<std::string>& InFollowSet = {});

	//	bool MakeNullable();

	//	bool AddFistElement(const std::string& Element);
	//	bool AddFistElement(const std::set<std::string>& Elements);
	//	bool AddFollowElement(const std::string& Element);
	//	bool AddFollowElement(const std::set<std::string>& Elements);
	//};

	class PARSER_API ParsingTable
	{
	protected:
		// ParserConfig* m_Config;
		// NonTerminal -> [Token -> Production]
		// std::map<std::string, std::map<std::string, ParserConfigElement*>> m_PredictionMap;
		std::map<int, std::map<int, int>> m_PredictionMap;

	public:
		ParsingTable();
		// ParsingTable(ParserConfig* InConfig);
		ParsingTable(const std::map<int, std::map<int, int>>& InPredictionMap);
		~ParsingTable();

	protected:
		// void CreateFirstFollowTable(std::map<std::string, FirstFollowSet>& OutFirstFollowMap) const;
		// void FillPredictionTable(std::map<std::string, FirstFollowSet>& FirstFollowMap);
		//void SetProduction(const std::string& NonTerminal, const std::string& Token, ParserConfigElement* Production);

	public:
		// ParserConfigElement* GetProduction(const std::string& NonTerminal, const std::string& Token);
		int GetProductionIndex(int NonTerminal, int Token);
		bool SetProductionIndex(int NonTerminal, int Token, int LocalRuleIndex);
		const std::map<int, std::map<int, int>>& GetProductionMap() const { return m_PredictionMap; }
		// const std::map<std::string, std::map<std::string, ParserConfigElement*>>& GetProductionMap() const { return m_PredictionMap; }
		// ParserConfig* GetParserConfig() const { return m_Config; }
	};

}