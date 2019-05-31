#include "ExpressionVisitor.h"

float ExpressionVisitor::VisitRule_additive(Rule_additive* Context)
{
	return 0.0f;
}

float ExpressionVisitor::VisitRule_additive2(Rule_additive2* Context)
{
	return 0.0f;
}

float ExpressionVisitor::VisitRule_constant(Rule_constant* Context)
{
	if (Context->FLOAT())
	{

	}
	else if (Context->INTEGER())
	{

	}
	else
	{

	}
}

float ExpressionVisitor::VisitRule_expression(Rule_expression* Context)
{
	return 0.0f;
}

float ExpressionVisitor::VisitRule_multiplicative(Rule_multiplicative* Context)
{
	return 0.0f;
}

float ExpressionVisitor::VisitRule_multiplicative2(Rule_multiplicative2* Context)
{
	return 0.0f;
}
