#pragma once

#include <string>

#include "ParsingTable.h"

namespace ParserCore::ParseTable {

	class TableFactory
	{
	public:
		static bool Deserialize(ParsingTable*& OutTable, const std::string& InContent);
	};

}