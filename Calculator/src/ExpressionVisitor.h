#pragma once

#include "gen/GenVisitorBase.h"

class ExpressionVisitor : public Gen::GenVisitorBase<float>
{
public:
	virtual float VisitRule_additive(Gen::Rule_additive* Context) override;
	virtual float VisitRule_additive2(Gen::Rule_additive2* Context) override;
	virtual float VisitRule_constant(Gen::Rule_constant* Context) override;
	virtual float VisitRule_expression(Gen::Rule_expression* Context) override;
	virtual float VisitRule_multiplicative(Gen::Rule_multiplicative* Context) override;
	virtual float VisitRule_multiplicative2(Gen::Rule_multiplicative2* Context) override;
};

