#pragma once

#include "gen/GenVisitorBase.h"

class ExpressionVisitor : public GenVisitorBase<float>
{
public:
	virtual float VisitRule_additive(Rule_additive* Context);
	virtual float VisitRule_constant(Rule_constant* Context);
	virtual float VisitRule_divide(Rule_divide* Context);
	virtual float VisitRule_expression(Rule_expression* Context);
	virtual float VisitRule_multiplicative(Rule_multiplicative* Context);
	virtual float VisitRule_product(Rule_product* Context);
	virtual float VisitRule_subtract(Rule_subtract* Context);
	virtual float VisitRule_sum(Rule_sum* Context);
};

