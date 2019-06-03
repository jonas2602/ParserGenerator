#pragma once

//#include "../Core.h"
//#include "../Lexer/Token.h"
//#include "ParserConfig.h"


namespace ParserCore {

	class ParseTree
	{
	public:
		virtual ParseTree* GetParent() const = 0;
		virtual ParseTree* GetChild(int Index) const = 0;
		virtual int GetChildCount() const = 0;

		virtual void SetParent(ParseTree* InParent) = 0;
	};

}