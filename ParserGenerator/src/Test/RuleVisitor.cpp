#include "RuleVisitor.h"
#include <iostream>
#include "../ParserTypes.h"

std::set<std::vector<std::string>> RuleVisitor::VisitRule_parseror(Rule_parseror* Context)
{
	std::set<std::vector<std::string>> OutSet;

	// Get child sets and append them
	std::set<std::vector<std::string>> ListSet = VisitRule_parserlist(Context->parserlist());
	OutSet.insert(ListSet.begin(), ListSet.end());
	std::set<std::vector<std::string>> OrSet = VisitRule_parseror2(Context->parseror2());
	OutSet.insert(OrSet.begin(), OrSet.end());

	// if one child returns empty set, it can be interpreted as an allowed Epsilon at that point
	if (ListSet.empty() || OrSet.empty())
	{
		// Create Epsilon Element
		OutSet.insert({ ParserGenerator::EPSILON_S });
	}

	return OutSet;
}

std::set<std::vector<std::string>> RuleVisitor::VisitRule_parseror2(Rule_parseror2* Context)
{
	std::set<std::vector<std::string>> OutSet;

	// Could it be enough to check if one child is empty?
	if (Context->parserlist() && Context->parseror2())
	{
		// Get child sets and append them
		std::set<std::vector<std::string>> ListSet = VisitRule_parserlist(Context->parserlist());
		OutSet.insert(ListSet.begin(), ListSet.end());
		std::set<std::vector<std::string>> OrSet = VisitRule_parseror2(Context->parseror2());
		OutSet.insert(OrSet.begin(), OrSet.end());

		// if listset is empty, it can be interpreted as an allowed Epsilon at that point
		if (ListSet.empty())
		{
			// Create Epsilon Element
			OutSet.insert({ ParserGenerator::EPSILON_S });
		}
	}

	return OutSet;
}

std::set<std::vector<std::string>> RuleVisitor::VisitRule_parserlist(Rule_parserlist* Context)
{
	std::set<std::vector<std::string>> OutSet;
	if (Context->parserconst() && Context->parserlist())
	{
		// Get child sets
		std::set<std::vector<std::string>> ConstSet = VisitRule_parserconst(Context->parserconst());
		std::set<std::vector<std::string>> ListSet = VisitRule_parserlist(Context->parserlist());

		// One set is empty?
		if (ConstSet.empty() || ListSet.empty())
		{
			// Simply take the other one
			OutSet = ConstSet.empty() ? ListSet : ConstSet;
		}
		else
		{
			// Merge the child sets
			for (const std::vector<std::string>& ConstElement : ConstSet)
			{
				for (const std::vector<std::string>& ListElement : ListSet)
				{
					if (ParserGenerator::IsEpsilon(ConstElement))
					{
						// Add only list if const is epsilon
						OutSet.insert(ListElement);
					}
					else if (ParserGenerator::IsEpsilon(ListElement))
					{
						// Add only const if list is epsilon
						OutSet.insert(ConstElement);
					}
					else
					{
						// append lists if both contain values
						std::vector<std::string> NewElement(ConstElement);
						NewElement.insert(NewElement.end(), ListElement.begin(), ListElement.end());
						OutSet.insert(NewElement);
					}
				}
			}
		}
	}

	return OutSet;
}

std::set<std::vector<std::string>> RuleVisitor::VisitRule_parserconst(Rule_parserconst* Context)
{
	if (Context->LITERAL())
	{
		const std::string& LiteralText = Context->LITERAL()->GetText();
		std::string LiteralContent = LiteralText.substr(1, -1);

		std::string LiteralName = m_LiteralMap[LiteralContent];
		if (LiteralName.empty())
		{
			LiteralName = "LITERAL" + m_LiteralMap.size();
			m_LiteralMap[LiteralContent] = LiteralName;
		}

		return std::set<std::vector<std::string>>({ {LiteralName} });
	}

	if (Context->PARSERID())
	{
		return std::set<std::vector<std::string>>({ {Context->PARSERID()->GetText()} });
	}

	if (Context->LEXERID())
	{
		return std::set<std::vector<std::string>>({ {Context->LEXERID()->GetText()} });
	}

	if (Context->parseror())
	{
		return VisitRule_parseror(Context->parseror());
	}

	return std::set<std::vector<std::string>>();
}
