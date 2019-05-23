#pragma once

#include <set>
#include <string>
#include <map>

#include "../Parser/ParserConfig.h"
#include "Alphabet.h"
#include "../Parser/ParsingTable.h"

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

	class FirstFollowTable
	{
		ParserConfig* m_Config;
		Alphabet* m_Alphabet;
		std::map<std::string, FirstFollowSet> m_Data;

	public:
		FirstFollowTable(ParserConfig* InConfig, Alphabet* InAlphabet);
		~FirstFollowTable();

		void CreateParsingTable(ParsingTable* OutTable);

	protected:
		void FillFirstFollows();
		void SetProduction(ParsingTable* OutTable, const std::string& NonTerminal, const std::string& Token, ParserConfigElement* Production);
	};

}