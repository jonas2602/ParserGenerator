#include "ExpressionVisitor.h"

float ExpressionVisitor::VisitRule_additive(Gen::Rule_additive* Context)
{
	if (!Context->multiplicative() || !Context->additive2()) return 0.0f;

	float LeftValue = VisitRule_multiplicative(Context->multiplicative());
	float RightValue = VisitRule_additive2(Context->additive2());

	if (Context->additive2()->PLUS())
	{
		return LeftValue + RightValue;
	}
	else if (Context->additive2()->MINUS())
	{
		return LeftValue - RightValue;
	}
	else
	{
		// Unexpected Situation
		return LeftValue;
	}
}

float ExpressionVisitor::VisitRule_additive2(Gen::Rule_additive2* Context)
{
	if (!Context->multiplicative() || !Context->additive2()) return 0.0f;

	float LeftValue = VisitRule_multiplicative(Context->multiplicative());
	float RightValue = VisitRule_additive2(Context->additive2());

	if (Context->additive2()->PLUS())
	{
		return LeftValue + RightValue;
	}
	else if (Context->additive2()->MINUS())
	{
		return LeftValue - RightValue;
	}
	else
	{
		// Unexpected Situation
		return LeftValue;
	}
}

float ExpressionVisitor::VisitRule_constant(Gen::Rule_constant* Context)
{
	if (Context->FLOAT())
	{
		return std::stof(Context->FLOAT()->GetText());
	}
	else if (Context->INTEGER())
	{
		return std::stoi(Context->INTEGER()->GetText());
	}
	else
	{
		return VisitRule_additive(Context->additive());
	}
}

float ExpressionVisitor::VisitRule_expression(Gen::Rule_expression* Context)
{
	return VisitRule_additive(Context->additive());
}

float ExpressionVisitor::VisitRule_multiplicative(Gen::Rule_multiplicative* Context)
{
	if (!Context->constant() || !Context->multiplicative2()) return 0.0f;

	float LeftValue = VisitRule_constant(Context->constant());
	float RightValue = VisitRule_multiplicative2(Context->multiplicative2());

	if (Context->multiplicative2()->STAR())
	{
		return LeftValue * RightValue;
	}
	else if (Context->multiplicative2()->SLASH())
	{
		return LeftValue / RightValue;
	}
	else
	{
		// Unexpected Situation
		return LeftValue;
	}
}

float ExpressionVisitor::VisitRule_multiplicative2(Gen::Rule_multiplicative2* Context)
{
	if (!Context->constant() || !Context->multiplicative2()) return 0.0f;

	float LeftValue = VisitRule_constant(Context->constant());
	float RightValue = VisitRule_multiplicative2(Context->multiplicative2());

	if (Context->multiplicative2()->STAR())
	{
		return LeftValue * RightValue;
	}
	else if (Context->multiplicative2()->SLASH())
	{
		return LeftValue / RightValue;
	}
	else
	{
		// Unexpected Situation
		return LeftValue;
	}
}
