#pragma once

#include "ParseTree.h"

class Visitor
{
public:
	Visitor();
	~Visitor();

	float Visit(ParseNode_Production* ProductionNode);
};

