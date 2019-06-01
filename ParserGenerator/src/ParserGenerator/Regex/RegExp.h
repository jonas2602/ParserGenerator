#pragma once

#include <string>
#include <vector>
#include <set>

#include <ParserCore.h>
#include "NFA.h"
#include "Node.h"

namespace ParserGenerator {

	class RegExp
	{
	public:
		// Special signs
		static const char TAB = '\t';	// Horizontal Tabulator
		static const char LF = '\n';	// Line Feed / New Line
		static const char CR = '\r';	// Carriage Return
		static const char ASCII_MIN = 1;
		static const char ASCII_MAX = 126;

	protected:
		Node_BASE* m_Root;

	public:
		RegExp(Node_BASE* InRoot);
		RegExp(const std::string& InString);
		~RegExp();

		void Parse(NFA* OutMachine, const std::string& Name, int Priority);

	public:
		static Node_BASE* AND(const char& Left, const char& Right);
		static Node_BASE* AND(const char& Left, Node_BASE* Right);
		static Node_BASE* AND(Node_BASE* Left, const char& Right);
		static Node_BASE* AND(Node_BASE* Left, Node_BASE* Right);
		static Node_BASE* AND(const std::vector<char>& Content);
		static Node_BASE* AND(const std::vector<Node_BASE*>& Content);
		//static Node_BASE* AND(Node_BASE* Args, ...);

		static Node_BASE* OR(const char& Left, const char& Right);
		static Node_BASE* OR(const char& Left, Node_BASE* Right);
		static Node_BASE* OR(Node_BASE* Left, const char& Right);
		static Node_BASE* OR(Node_BASE* Left, Node_BASE* Right);
		static Node_BASE* OR(const std::vector<char>& Content);
		static Node_BASE* OR(const std::vector<Node_BASE*>& Content);

		static Node_BASE* STAR(const char& Content);
		static Node_BASE* STAR(Node_BASE* Content);

		// Internally converted from 'x+' -> 'xx*' 
		static Node_BASE* PLUS(const char& Content);
		static Node_BASE* PLUS(Node_BASE* Content);

		static Node_CONST* CONST(const char& Content);
		static Node_BASE* SEQUENCE(const std::string& Content);

		// Internally converted from '[min, max]' -> 'OR(min, ..., max)' 
		static Node_CONST* RANGE(const char& Min, const char& Max);

		static Node_CONST* LIST(const std::set<char>& Content);
		static Node_CONST* LIST(const std::vector<Node_CONST*>& Content);

		// Internally converted from '.' -> [32, 126] 
		static Node_BASE* ANY();

		static Node_BASE* EXCEPT(const std::vector<char>& Excluded);
		static Node_BASE* EXCEPT(const std::vector<Node_CONST*>& Excluded);

		static Node_BASE* OPTIONAL(const char& Content);
		static Node_BASE* OPTIONAL(Node_BASE* Content);
	};

}