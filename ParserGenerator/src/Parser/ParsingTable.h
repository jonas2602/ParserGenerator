#pragma once

#include <string>
#include <map>
#include <set>
#include "ParserConfig.h"

namespace ParserGenerator {

	struct FirstFollowSet
	{
		bool m_bNullable;
		std::set<std::string> m_FirstSet;
		std::set<std::string> m_FollowSet;

		FirstFollowSet(bool InNullable = false, const std::set<std::string>& InFirstSet = {}, const std::set<std::string>& InFollowSet = {});

		bool MakeNullable();

		bool AddFistElement(const std::string& Element);
		bool AddFistElement(const std::set<std::string>& Elements);
		bool AddFollowElement(const std::string& Element);
		bool AddFollowElement(const std::set<std::string>& Elements);
	};

	class ParsingTable
	{
	protected:
		ParserConfig* m_Config;
		// NonTerminal -> [Token -> Production]
		std::map<std::string, std::map<std::string, ParserConfigElement*>> m_PredictionMap;

	public:
		ParsingTable(ParserConfig* InConfig);
		~ParsingTable();

	protected:
		void CreateFirstFollowTable(std::map<std::string, FirstFollowSet>& OutFirstFollowMap) const;
		void FillPredictionTable(std::map<std::string, FirstFollowSet>& FirstFollowMap);
		void SetProduction(const std::string& NonTerminal, const std::string& Token, ParserConfigElement* Production);

	public:
		ParserConfigElement* GetProduction(const std::string& NonTerminal, const std::string& Token);
	};

}