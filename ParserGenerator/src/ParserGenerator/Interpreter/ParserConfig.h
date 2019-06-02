#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <set>
#include <map>

#include <ParserCore.h>

namespace ParserGenerator {

	enum ERuleElementType {
		RULE,
		TERMINAL,
		LITERAL,
	};

	struct RuleElement
	{
		std::string m_Content;
		ERuleElementType m_Type;

		RuleElement(const std::string& InContent, ERuleElementType InType)
			: m_Content(InContent), m_Type(InType)
		{ }

		bool IsNonTerminal() { return m_Type == ERuleElementType::RULE; }
		bool IsEpsilon() { return PC::IsEpsilon(m_Content); }
		static RuleElement* EPSIlON_ELEMENT;
	};

	struct RuleDefinition
	{
		std::string m_NonTerminal;
		std::vector<RuleElement*> m_RuleElements;
		std::vector<std::string> m_TokenClasses;
		int m_LocalRuleIndex;

		RuleDefinition(const std::string& InNonTerminal, const std::vector<std::string>& InTokenClasses, int InLocalRuleIndex)
			: m_NonTerminal(InNonTerminal), m_TokenClasses(InTokenClasses), m_LocalRuleIndex(InLocalRuleIndex)
		{ }

		RuleDefinition(const std::string& InNonTerminal, const std::vector<RuleElement*>& InRuleElements, int InLocalRuleIndex)
			: m_NonTerminal(InNonTerminal), m_RuleElements(InRuleElements), m_LocalRuleIndex(InLocalRuleIndex)
		{ }

		int GetTokenCount() const { return (int)m_TokenClasses.size(); }
		const std::string& GetTokenClassAtIndex(int Index) const { return m_TokenClasses[Index]; }

		bool IsEpsilon() { return m_RuleElements.size() == 0 || m_RuleElements[0]->IsEpsilon(); }
		static bool IsEpsilon(std::vector<RuleElement*> ElementList) { return ElementList.size() == 0 || ElementList[0]->IsEpsilon(); }

		friend std::ostream& operator<<(std::ostream& os, const RuleDefinition* InProduction)
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
		std::vector<RuleDefinition*> m_ProductionList;
		std::set<std::string> m_NonTerminals;
		std::set<std::string> m_Terminals;

		std::map<std::string, int> m_RuleCountMap;
		std::map<std::string, std::vector<RuleDefinition*>> m_ProductionMap;

	public:
		ParserConfig();
		~ParserConfig();

		void AddProduction(const std::string& NonTerminal, const std::vector<std::string>& TokenClasses);
		void AddProduction(const std::string& NonTerminal, const std::vector<RuleElement*>& RuleElements);
		void FillTerminals();

		bool Validate(const std::set<std::string>& TerminalList);
		void Normalize();

		std::vector<RuleDefinition*> GetAllProductionsForNonTerminal(const std::string& NonTerminal) const;
		const std::vector<RuleDefinition*>& GetProductionList() const { return m_ProductionList; }
		int GetProductionCount() const { return (int)m_ProductionList.size(); }

		const std::vector<std::string>& GetRuleElements(const std::string& NonTerminalName, int LocalRuleIndex);

		const std::set<std::string>& GetNonTerminals() const { return m_NonTerminals; }
		const std::set<std::string>& GetTerminals() const { return m_Terminals; }

		bool IsNonTerminal(const std::string& Token) const;

		std::map<std::string, int> GetNonTerminalMap() const;
	};

}