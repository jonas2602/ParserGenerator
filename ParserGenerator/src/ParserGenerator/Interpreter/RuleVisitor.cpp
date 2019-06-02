#include "RuleVisitor.h"
#include <iostream>
#include "../Utils/StringUtils.h"

namespace ParserGenerator {

	std::set<std::vector<RuleElement*>> RuleVisitor::VisitRule_parseror(Rule_parseror* Context)
	{
		std::set<std::vector<RuleElement*>> OutSet;

		// Get child sets and append them
		std::set<std::vector<RuleElement*>> ListSet = VisitRule_parserlist(Context->parserlist());
		OutSet.insert(ListSet.begin(), ListSet.end());
		std::set<std::vector<RuleElement*>> OrSet = VisitRule_parseror2(Context->parseror2());
		OutSet.insert(OrSet.begin(), OrSet.end());

		// if list child returns empty set, it can be interpreted as an allowed Epsilon at that point
		if (ListSet.empty())
		{
			// Create Epsilon Element
			OutSet.insert({ RuleElement::EPSIlON_ELEMENT });
		}

		return OutSet;
	}

	std::set<std::vector<RuleElement*>> RuleVisitor::VisitRule_parseror2(Rule_parseror2* Context)
	{
		std::set<std::vector<RuleElement*>> OutSet;

		// Could it be enough to check if one child is empty?
		if (Context->parserlist() && Context->parseror2())
		{
			// Get child sets and append them
			std::set<std::vector<RuleElement*>> ListSet = VisitRule_parserlist(Context->parserlist());
			OutSet.insert(ListSet.begin(), ListSet.end());
			std::set<std::vector<RuleElement*>> OrSet = VisitRule_parseror2(Context->parseror2());
			OutSet.insert(OrSet.begin(), OrSet.end());

			// if listset is empty, it can be interpreted as an allowed Epsilon at that point
			if (ListSet.empty())
			{
				// Create Epsilon Element
				OutSet.insert({ RuleElement::EPSIlON_ELEMENT });
			}
		}

		return OutSet;
	}

	std::set<std::vector<RuleElement*>> RuleVisitor::VisitRule_parserlist(Rule_parserlist* Context)
	{
		std::set<std::vector<RuleElement*>> OutSet;
		if (Context->parserconst() && Context->parserlist())
		{
			// Get child sets
			std::set<std::vector<RuleElement*>> ConstSet = VisitRule_parserconst(Context->parserconst());
			std::set<std::vector<RuleElement*>> ListSet = VisitRule_parserlist(Context->parserlist());

			// One set is empty?
			if (ConstSet.empty() || ListSet.empty())
			{
				// Simply take the other one
				OutSet = ConstSet.empty() ? ListSet : ConstSet;
			}
			else
			{
				// Merge the child sets
				for (const std::vector<RuleElement*>& ConstElement : ConstSet)
				{
					for (const std::vector<RuleElement*>& ListElement : ListSet)
					{
						if (RuleDefinition::IsEpsilon(ConstElement))
						{
							// Add only list if const is epsilon
							OutSet.insert(ListElement);
						}
						else if (RuleDefinition::IsEpsilon(ListElement))
						{
							// Add only const if list is epsilon
							OutSet.insert(ConstElement);
						}
						else
						{
							// append lists if both contain values
							std::vector<RuleElement*> NewElement(ConstElement);
							NewElement.insert(NewElement.end(), ListElement.begin(), ListElement.end());
							OutSet.insert(NewElement);
						}
					}
				}
			}
		}

		return OutSet;
	}

	std::set<std::vector<RuleElement*>> RuleVisitor::VisitRule_parserconst(Rule_parserconst* Context)
	{
		if (Context->LITERAL())
		{
			const std::string& LiteralText = Context->LITERAL()->GetText();
			std::string LiteralContent = StringUtils::InterpretLiteral(LiteralText.substr(1, LiteralText.size() - 2));

			RuleElement* Literal = m_LiteralMap[LiteralContent];
			if (!Literal)
			{
				Literal = new RuleElement("", ERuleElementType::LITERAL);
				m_LiteralMap[LiteralContent] = Literal;
			}

			return std::set<std::vector<RuleElement*>>({ {Literal} });
		}

		if (Context->PARSERID())
		{
			const std::string& RuleName = Context->PARSERID()->GetText();
			RuleElement* NonTerminal = m_NonTerminalMap[RuleName];
			if (!NonTerminal)
			{
				NonTerminal = new RuleElement(RuleName, ERuleElementType::RULE);
				m_NonTerminalMap[RuleName] = NonTerminal;
			}

			return std::set<std::vector<RuleElement*>>({ {NonTerminal} });
		}

		if (Context->LEXERID())
		{
			const std::string& TerminalName = Context->LEXERID()->GetText();
			RuleElement* Terminal = m_TerminalMap[TerminalName];
			if (!Terminal)
			{
				Terminal = new RuleElement(TerminalName, ERuleElementType::TERMINAL);
				m_TerminalMap[TerminalName] = Terminal;
			}

			return std::set<std::vector<RuleElement*>>({ {Terminal} });
		}

		if (Context->parseror())
		{
			return VisitRule_parseror(Context->parseror());
		}

		return std::set<std::vector<RuleElement*>>();
	}

}