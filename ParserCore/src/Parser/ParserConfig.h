#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <set>
#include <map>

namespace ParserCore {

	struct ParserConfigElement
	{
		std::string m_NonTerminal;
		std::vector<std::string> m_TokenClasses;
		int m_LocalRuleIndex;

		ParserConfigElement(const std::string& InNonTerminal, const std::vector<std::string>& InTokenClasses, int InLocalRuleIndex)
			: m_NonTerminal(InNonTerminal), m_TokenClasses(InTokenClasses), m_LocalRuleIndex(InLocalRuleIndex)
		{ }

		int GetTokenCount() const { return (int)m_TokenClasses.size(); }
		const std::string& GetTokenClassAtIndex(int Index) const { return m_TokenClasses[Index]; }

		friend std::ostream& operator<<(std::ostream& os, const ParserConfigElement* InProduction)
		{
			// write obj to stream
			os << InProduction->m_NonTerminal << " ->";
			for (const std::string& TokenClass : InProduction->m_TokenClasses)
			{
				os << " " << TokenClass;
			}

			return os;
		}
	};

	class ParserConfig
	{
	protected:
		std::vector<ParserConfigElement*> m_ProductionList;
		std::set<std::string> m_NonTerminals;
		std::set<std::string> m_Terminals;

		std::map<std::string, int> m_RuleCountMap;

	public:
		ParserConfig();
		~ParserConfig();

		void AddProduction(const std::string& NonTerminal, const std::vector<std::string>& TokenClasses);
		void FillTerminals();

		bool Validate(const std::set<std::string>& TerminalList);
		void Normalize();

		std::vector<ParserConfigElement*> GetAllProductionsForNonTerminal(const std::string& NonTerminal) const;
		const std::vector<ParserConfigElement*>& GetProductionList() const { return m_ProductionList; }
		int GetProductionCount() const { return (int)m_ProductionList.size(); }

		const std::vector<std::string>& GetRuleElements(const std::string& NonTerminalName, int LocalRuleIndex);

		const std::set<std::string>& GetNonTerminals() const { return m_NonTerminals; }
		const std::set<std::string>& GetTerminals() const { return m_Terminals; }

		bool IsNonTerminal(const std::string& Token) const;

		std::map<std::string, int> GetNonTerminalMap() const;
	};

}