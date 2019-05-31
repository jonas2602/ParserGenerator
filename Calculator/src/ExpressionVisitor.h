#pragma once

#include "gen/GenVisitorBase.h"

class ExpressionVisitor : public GenVisitorBase<float>
{
public:
	virtual float VisitRule_additive(Rule_additive* Context) override;
	virtual float VisitRule_additive2(Rule_additive2* Context) override;
	virtual float VisitRule_constant(Rule_constant* Context) override;
	virtual float VisitRule_expression(Rule_expression* Context) override;
	virtual float VisitRule_multiplicative(Rule_multiplicative* Context) override;
	virtual float VisitRule_multiplicative2(Rule_multiplicative2* Context) override;
};

