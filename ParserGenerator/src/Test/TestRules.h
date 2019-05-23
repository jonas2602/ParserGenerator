#pragma once

#include "../Parser/ParseTree/RuleNode.h"
#include "TestAlphabet.h"

class Rule_parseror;

class Rule_parserrule : public ParserGenerator::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERRULE; }

public:
	ParserGenerator::TokenNode* PARSERID() { return GetToken(ETokenType::PARSERID, 0); }
	ParserGenerator::TokenNode* COLON() { return GetToken(ETokenType::COLON, 0); }
	Rule_parseror* parseror() { return GetRule<Rule_parseror>(0); }
	ParserGenerator::TokenNode* SEMICOLON() { return GetToken(ETokenType::SEMICOLON, 0); }
};

class Rule_parseror : public ParserGenerator::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSEROR; }

public:
};

class Rule_parseror2 : public ParserGenerator::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSEROR2; }

public:
};

class Rule_parserlist : public ParserGenerator::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERLIST; }

public:
};

class Rule_parserconst : public ParserGenerator::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERCONST; }

public:
};
