#pragma once

#include "GrammarParser/GrammarVisitorBase.h"
#include "../Regex/RegExp.h"

namespace ParserGenerator {

	class TokenVisitor : public GrammarVisitorBase<Node_BASE*>
	{
	public:
		virtual Node_BASE* VisitRule_action(Rule_action* Context) override;
		virtual Node_BASE* VisitRule_regex(Rule_regex* Context) override;
		virtual Node_BASE* VisitRule_lexeror(Rule_lexeror* Context) override;
		virtual Node_BASE* VisitRule_lexeror2(Rule_lexeror2* Context) override;
		virtual Node_BASE* VisitRule_operatorr(Rule_operatorr* Context) override;
		virtual Node_BASE* VisitRule_lexerconst(Rule_lexerconst* Context) override;
	};

}