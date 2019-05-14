#pragma once

#include <string>
#include <vector>
#include <set>

namespace ParserGenerator {

	struct ParserConfigElement
	{
		std::string m_NonTerminal;
		std::vector<std::string> m_TokenClasses;

		ParserConfigElement(const std::string& InNonTerminal, const std::vector<std::string>& InTokenClasses)
			: m_NonTerminal(InNonTerminal), m_TokenClasses(InTokenClasses)
		{ }

		int GetTokenCount() const { return (int)m_TokenClasses.size(); }
		const std::string& GetTokenClassAtIndex(int Index) const { return m_TokenClasses[Index]; }
	};

	class ParserConfig
	{
	public:
		// End Of Stream Token Type
		static const std::string EOS;

	protected:
		std::string m_StartNonTerminal;
		std::vector<ParserConfigElement*> m_ProductionList;
		std::set<std::string> m_NonTerminals;
		std::set<std::string> m_Terminals;

	public:
		ParserConfig(const std::string& InStartSymbol);
		~ParserConfig();

		void AddProduction(const std::string& NonTerminal, const std::vector<std::string>& TokenClasses);
		void FillTerminals();
		void Normalize();

		std::vector<ParserConfigElement*> GetAllProductionsForNonTerminal(const std::string& NonTerminal) const;
		const std::vector<ParserConfigElement*>& GetProductionList() const { return m_ProductionList; }
		int GetProductionCount() const { return (int)m_ProductionList.size(); }

		const std::set<std::string>& GetNonTerminals() const { return m_NonTerminals; }
		const std::set<std::string>& GetTerminals() const { return m_Terminals; }
		const std::string& GetStartNonTerminal() const { return m_StartNonTerminal; }

		bool IsNonTerminal(const std::string& Token) const;
	};

}