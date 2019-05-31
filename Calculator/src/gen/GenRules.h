// Automatically generated File
#pragma once

#include "GenAlphabet.h"
#include <ParserCore.h>
class Rule_additive;
class Rule_additive2;
class Rule_constant;
class Rule_expression;
class Rule_multiplicative;
class Rule_multiplicative2;

class Rule_additive: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::ADDITIVE; }

public:
	Rule_additive2* additive2() const { return GetRule<Rule_additive2>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

};

class Rule_additive2: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::ADDITIVE2; }

public:
	ParserGenerator::TokenNode* MINUS() const { return GetToken(ETokenType::MINUS, 0); }
	ParserGenerator::TokenNode* PLUS() const { return GetToken(ETokenType::PLUS, 0); }
	Rule_additive2* additive2() const { return GetRule<Rule_additive2>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

};

class Rule_constant: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::CONSTANT; }

public:
	ParserGenerator::TokenNode* FLOAT() const { return GetToken(ETokenType::FLOAT, 0); }
	ParserGenerator::TokenNode* INTEGER() const { return GetToken(ETokenType::INTEGER, 0); }
	ParserGenerator::TokenNode* LP() const { return GetToken(ETokenType::LP, 0); }
	ParserGenerator::TokenNode* RP() const { return GetToken(ETokenType::RP, 0); }
	Rule_additive* additive() const { return GetRule<Rule_additive>(0); }

};

class Rule_expression: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::EXPRESSION; }

public:
	Rule_additive* additive() const { return GetRule<Rule_additive>(0); }

};

class Rule_multiplicative: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::MULTIPLICATIVE; }

public:
	Rule_constant* constant() const { return GetRule<Rule_constant>(0); }
	Rule_multiplicative2* multiplicative2() const { return GetRule<Rule_multiplicative2>(0); }

};

class Rule_multiplicative2: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::MULTIPLICATIVE2; }

public:
	ParserGenerator::TokenNode* SLASH() const { return GetToken(ETokenType::SLASH, 0); }
	ParserGenerator::TokenNode* STAR() const { return GetToken(ETokenType::STAR, 0); }
	Rule_constant* constant() const { return GetRule<Rule_constant>(0); }
	Rule_multiplicative2* multiplicative2() const { return GetRule<Rule_multiplicative2>(0); }

};
