#pragma once

#include <map>
#include <string>
#include <functional>

#include "ParseTree.h"

class Visitor
{
protected:
	std::map<std::string, std::function<void(void)>> m_FunctionMap;
	//std::map<std::string, void (Visitor::*)()> m_FunctionMap;

public:
	Visitor();
	~Visitor();

	void AddFunctionPointer();

	void TestFunction();

	float Visit(ParseNode_Production* ProductionNode);
};

