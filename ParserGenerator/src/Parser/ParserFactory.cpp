#include "ParserFactory.h"



namespace ParserGenerator {

	bool ParserFactory::Serialize(Parser* InParser, const std::string& FilePath)
	{
		ParserConfig* Config = InParser->GetParserConfig();
		for (const std::string& Terminal : Config->GetTerminals())
		{

		}

		for (const std::string& NonTerminal : Config->GetNonTerminals())
		{

		}

		ParsingTable* Table = InParser->GetParsingTable();
		for (const std::pair<std::string>& Table->GetProductionMap())
		{

		}

		return false;
	}

	bool ParserFactory::Deserialize(Parser*& OutParser, const std::string& FilePath)
	{
		return false;
	}
}