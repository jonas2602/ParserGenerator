#include "TokenVisitor.h"
#include <iostream>
#include "ListParser/ListInterpreter.h"

ParserCore::Node_BASE* TokenVisitor::VisitRule_action(Rule_action* Context)
{
	return nullptr;
}

ParserCore::Node_BASE* TokenVisitor::VisitRule_regex(Rule_regex* Context)
{
	if (!Context->lexeror() || !Context->regex()) return nullptr;

	ParserCore::Node_BASE* LeftNode = VisitRule_lexeror(Context->lexeror());
	ParserCore::Node_BASE* RightNode = VisitRule_regex(Context->regex());
	// assume that when the right child is valid the left must also be valid
	if (RightNode)
	{
		return ParserCore::RegExp::AND(LeftNode, RightNode);
	}

	// Only left child is valid or none is valid
	return LeftNode;
}

ParserCore::Node_BASE* TokenVisitor::VisitRule_lexeror(Rule_lexeror* Context)
{
	ParserCore::Node_BASE* LeftNode = VisitRule_operator(Context->operatorr());
	ParserCore::Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

	if (LeftNode && RightNode)
	{
		return ParserCore::RegExp::OR(LeftNode, RightNode);
	}

	return LeftNode;
}

ParserCore::Node_BASE* TokenVisitor::VisitRule_lexeror2(Rule_lexeror2* Context)
{
	if (!Context->lexeror2() || !Context->operatorr()) return nullptr;

	ParserCore::Node_BASE* LeftNode = VisitRule_operator(Context->operatorr());
	ParserCore::Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

	if (LeftNode && RightNode)
	{
		return ParserCore::RegExp::OR(LeftNode, RightNode);
	}

	return LeftNode;
}

ParserCore::Node_BASE* TokenVisitor::VisitRule_operator(Rule_operator* Context)
{
	// Create Operator Content
	ParserCore::Node_BASE* Content = VisitRule_lexerconst(Context->lexerconst());

	// Switched chosen operator
	if (Context->operator2()->STAR())
	{
		return ParserCore::RegExp::STAR(Content);
	}
	if (Context->operator2()->PLUS())
	{
		return ParserCore::RegExp::PLUS(Content);
	}
	if (Context->operator2()->QUESTIONMARK())
	{
		return ParserCore::RegExp::OPTIONAL(Content);
	}

	// No Operator Chosen
	return Content;
}

// ParserCore::Node_BASE* TokenVisitor::VisitRule_operator2(Rule_operator2* Context)
// {
// 	return nullptr;
// }

ParserCore::Node_BASE* TokenVisitor::VisitRule_lexerconst(Rule_lexerconst* Context)
{
	if (Context->regex())
	{
		return VisitRule_regex(Context->regex());
	}
	if (Context->LEXERID())
	{
		std::cout << "LEXERID currenty not supported in regex creation" << std::endl;
		// TODO: Copy content of regex in here
		return nullptr;
	}
	if (Context->DOT())
	{
		return ParserCore::RegExp::ANY();
	}
	if (Context->LITERAL())
	{
		const std::string& LiteralString = Context->LITERAL()->GetText();
		std::string LiteralContent = LiteralString.substr(1, LiteralString.size() - 2);
		return ParserCore::RegExp::SEQUENCE(LiteralContent);
	}
	if (Context->CHARSET())
	{
		const std::string& CharsetString = Context->CHARSET()->GetText();
		std::string CharsetContent = CharsetString.substr(1, CharsetString.size() - 2);
 		std::vector<ParserCore::Node_CONST*> CharsetElements;
		ListInterpreter::Analyse(CharsetContent, CharsetElements);

		return ParserCore::RegExp::LIST(CharsetElements);
	}

	return nullptr;
}
