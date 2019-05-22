#pragma once


class ParserBuilder
{
public:
	ParserBuilder(ParserConfig* PConfig, LexerConfig* LConfig);
	// Generate Automaton
	// Generate Table

	void Generate(const std::string& RootPath);
	// Serialize DFA/Table
	// Generate Files
};

