#include "Visitor.h"
#include <iostream>


namespace ParserGenerator {

	Visitor::Visitor()
	{
	}


	Visitor::~Visitor()
	{
	}

	void Visitor::AddFunctionPointer()
	{
		m_FunctionMap["S"] = std::bind(&Visitor::TestFunction, this);
		//m_FunctionMap.emplace("S", &Visitor::TestFunction);
	}

	void Visitor::TestFunction()
	{
		std::cout << "function called" << std::endl;
	}

	float Visitor::Visit(ParseNode_Production* ProductionNode)
	{
		//(this->*m_FunctionMap["S"])();
		m_FunctionMap["S"]();
		return 0.0f;
	}

}