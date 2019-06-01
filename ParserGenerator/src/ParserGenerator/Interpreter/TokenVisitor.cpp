#include "TokenVisitor.h"
#include <iostream>
#include "ListInterpreter.h"

namespace ParserGenerator {

	Node_BASE* TokenVisitor::VisitRule_action(Rule_action* Context)
	{
		return nullptr;
	}

	Node_BASE* TokenVisitor::VisitRule_regex(Rule_regex* Context)
	{
		if (!Context->lexeror() || !Context->regex()) return nullptr;

		Node_BASE* LeftNode = VisitRule_lexeror(Context->lexeror());
		Node_BASE* RightNode = VisitRule_regex(Context->regex());
		// assume that when the right child is valid the left must also be valid
		if (RightNode)
		{
			return RegExp::AND(LeftNode, RightNode);
		}

		// Only left child is valid or none is valid
		return LeftNode;
	}

	Node_BASE* TokenVisitor::VisitRule_lexeror(Rule_lexeror* Context)
	{
		Node_BASE* LeftNode = VisitRule_operatorr(Context->operatorr());
		Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

		if (LeftNode && RightNode)
		{
			return RegExp::OR(LeftNode, RightNode);
		}

		return LeftNode;
	}

	Node_BASE* TokenVisitor::VisitRule_lexeror2(Rule_lexeror2* Context)
	{
		if (!Context->lexeror2() || !Context->operatorr()) return nullptr;

		Node_BASE* LeftNode = VisitRule_operatorr(Context->operatorr());
		Node_BASE* RightNode = VisitRule_lexeror2(Context->lexeror2());

		if (LeftNode && RightNode)
		{
			return RegExp::OR(LeftNode, RightNode);
		}

		return LeftNode;
	}

	Node_BASE* TokenVisitor::VisitRule_operatorr(Rule_operatorr* Context)
	{
		// Create Operator Content
		Node_BASE* Content = VisitRule_lexerconst(Context->lexerconst());

		// Switched chosen operator
		if (Context->operatorr2()->STAR())
		{
			return RegExp::STAR(Content);
		}
		if (Context->operatorr2()->PLUS())
		{
			return RegExp::PLUS(Content);
		}
		if (Context->operatorr2()->QUESTIONMARK())
		{
			return RegExp::OPTIONAL(Content);
		}

		// No Operator Chosen
		return Content;
	}

	// ParserCore::Node_BASE* TokenVisitor::VisitRule_operator2(Rule_operator2* Context)
	// {
	// 	return nullptr;
	// }

	Node_BASE* TokenVisitor::VisitRule_lexerconst(Rule_lexerconst* Context)
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
			return RegExp::ANY();
		}
		if (Context->LITERAL())
		{
			const std::string& LiteralString = Context->LITERAL()->GetText();
			std::string LiteralContent = LiteralString.substr(1, LiteralString.size() - 2);
			return RegExp::SEQUENCE(LiteralContent);
		}
		if (Context->CHARSET())
		{
			std::string CharsetString = Context->CHARSET()->GetText();
			bool bIsExcept = false;
			if (CharsetString.front() == '~')
			{
				bIsExcept = true;
				CharsetString = CharsetString.substr(1);
			}
			std::string CharsetContent = CharsetString.substr(1, CharsetString.size() - 2);
			std::vector<Node_CONST*> CharsetElements;
			ListInterpreter::Analyse(CharsetContent, CharsetElements);

			return bIsExcept ? RegExp::EXCEPT(CharsetElements) : RegExp::LIST(CharsetElements);
		}

		return nullptr;
	}

}