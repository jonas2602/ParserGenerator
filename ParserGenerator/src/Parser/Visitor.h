#pragma once

#include <map>
#include <string>
#include <functional>

#include "../Core.h"
#include "ParseTree/RuleNode.h"

namespace ParserGenerator {

	template<typename T>
	class Visitor
	{
	protected:
		//std::map<int, std::function<void(void)>> m_FunctionMap;
		//std::map<std::string, void (Visitor::*)()> m_FunctionMap;

	public:
		//Visitor();
		//~Visitor();

		//void AddFunctionPointer();
		//void TestFunction();
		//float Visit(RuleNode* ProductionNode);

		/*template<typename U>
		T Visit(U* Context)
		{
			static_assert(false);
		}*/

	protected:
		//virtual void CreateFunctionMap() = 0;
	};


}