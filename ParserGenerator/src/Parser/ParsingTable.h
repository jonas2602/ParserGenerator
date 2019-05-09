#pragma once

#include <string>
#include <map>
#include <set>
#include "ParserConfig.h"


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

struct PredictionTuple
{
	std::string m_NonTerminal;
	std::string m_Token;

	PredictionTuple(const std::string& InNonTerminal, const std::string& InToken)
		: m_NonTerminal(InNonTerminal), m_Token(InToken)
	{ }

	bool operator==(const PredictionTuple& InTupel)
	{
		return m_NonTerminal == InTupel.m_NonTerminal
			&& m_Token == InTupel.m_Token;
	}
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

public:
	ParserConfigElement* GetProduction(const std::string& NonTerminal, const std::string& Token);
};

