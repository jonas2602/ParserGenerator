#include "TokenVisitor.h"
#include <iostream>
#include "ListParser/ListInterpreter.h"

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_action(Rule_action* Context)
{
	return nullptr;
}

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_regex(Rule_regex* Context)
{
	if (!Context->lexeror() || !Context->regex()) return nullptr;

	ParserGenerator::Node_BASE* LeftNode = VisitRule_lexeror(Context->lexeror());
	ParserGenerator::Node_BASE* RightNode = VisitRule_regex(Context->regex());
	// assume that when the right child is valid the left must also be valid
	if (RightNode)
	{
		return ParserGenerator::RegExp::AND(LeftNode, RightNode);
	}

	// Only left child is valid or none is valid
	return LeftNode;
}

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_lexeror(Rule_lexeror* Context)
{
	ParserGenerator::Node_BASE* LeftNode = VisitRule_operator(Context->operatorr());
	ParserGenerator::Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

	if (LeftNode && RightNode)
	{
		return ParserGenerator::RegExp::OR(LeftNode, RightNode);
	}

	return LeftNode;
}

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_lexeror2(Rule_lexeror2* Context)
{
	if (!Context->lexeror2() || !Context->operatorr()) return nullptr;

	ParserGenerator::Node_BASE* LeftNode = VisitRule_operator(Context->operatorr());
	ParserGenerator::Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

	if (LeftNode && RightNode)
	{
		return ParserGenerator::RegExp::OR(LeftNode, RightNode);
	}

	return LeftNode;
}

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_operator(Rule_operator* Context)
{
	// Create Operator Content
	ParserGenerator::Node_BASE* Content = VisitRule_lexerconst(Context->lexerconst());

	// Switched chosen operator
	if (Context->operator2()->STAR())
	{
		return ParserGenerator::RegExp::STAR(Content);
	}
	if (Context->operator2()->PLUS())
	{
		return ParserGenerator::RegExp::PLUS(Content);
	}
	if (Context->operator2()->QUESTIONMARK())
	{
		return ParserGenerator::RegExp::OPTIONAL(Content);
	}

	// No Operator Chosen
	return Content;
}

// ParserGenerator::Node_BASE* TokenVisitor::VisitRule_operator2(Rule_operator2* Context)
// {
// 	return nullptr;
// }

ParserGenerator::Node_BASE* TokenVisitor::VisitRule_lexerconst(Rule_lexerconst* Context)
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
		return ParserGenerator::RegExp::ANY();
	}
	if (Context->LITERAL())
	{
		return ParserGenerator::RegExp::SEQUENCE(Context->LITERAL()->GetText());
	}
	if (Context->CHARSET())
	{
		// TODO: Interpret the charset content
		const std::string& CharsetString = Context->CHARSET()->GetText();
		std::string CharsetContent = CharsetString.substr(1, CharsetString.size() - 2);
		std::vector<ParserGenerator::Node_CONST*> CharsetElements;
		ListInterpreter::Analyse(CharsetContent, CharsetElements);

		return ParserGenerator::RegExp::LIST(CharsetElements);
	}

	return nullptr;
}
