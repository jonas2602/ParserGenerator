// Automatically generated File
#pragma once

#include "GenRules.h"
#include <Parser.h>

template<typename T>
class GenVisitorBase: public ParserGenerator::Visitor<T>
{
public:
	virtual T VisitRule_additive(Rule_additive* Context) { return T(); }
	virtual T VisitRule_constant(Rule_constant* Context) { return T(); }
	virtual T VisitRule_divide(Rule_divide* Context) { return T(); }
	virtual T VisitRule_expression(Rule_expression* Context) { return T(); }
	virtual T VisitRule_multiplicative(Rule_multiplicative* Context) { return T(); }
	virtual T VisitRule_product(Rule_product* Context) { return T(); }
	virtual T VisitRule_subtract(Rule_subtract* Context) { return T(); }
	virtual T VisitRule_sum(Rule_sum* Context) { return T(); }

public:
	template<typename U>
	T Visit(U* Context)
	{
		static_assert(false);
	}
	template<>
	T Visit<Rule_additive>(Rule_additive* Context) { return VisitRule_additive(Context); }
	template<>
	T Visit<Rule_constant>(Rule_constant* Context) { return VisitRule_constant(Context); }
	template<>
	T Visit<Rule_divide>(Rule_divide* Context) { return VisitRule_divide(Context); }
	template<>
	T Visit<Rule_expression>(Rule_expression* Context) { return VisitRule_expression(Context); }
	template<>
	T Visit<Rule_multiplicative>(Rule_multiplicative* Context) { return VisitRule_multiplicative(Context); }
	template<>
	T Visit<Rule_product>(Rule_product* Context) { return VisitRule_product(Context); }
	template<>
	T Visit<Rule_subtract>(Rule_subtract* Context) { return VisitRule_subtract(Context); }
	template<>
	T Visit<Rule_sum>(Rule_sum* Context) { return VisitRule_sum(Context); }

};
