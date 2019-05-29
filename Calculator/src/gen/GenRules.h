// Automatically generated File
#pragma once

#include "GenAlphabet.h"
#include <Parser.h>
class Rule_additive;
class Rule_constant;
class Rule_divide;
class Rule_expression;
class Rule_multiplicative;
class Rule_product;
class Rule_subtract;
class Rule_sum;

class Rule_additive: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::ADDITIVE; }

public:
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }
	Rule_subtract* subtract() const { return GetRule<Rule_subtract>(0); }
	Rule_sum* sum() const { return GetRule<Rule_sum>(0); }

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

class Rule_divide: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::DIVIDE; }

public:
	ParserGenerator::TokenNode* SLASH() const { return GetToken(ETokenType::SLASH, 0); }
	Rule_constant* constant() const { return GetRule<Rule_constant>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

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
	Rule_divide* divide() const { return GetRule<Rule_divide>(0); }
	Rule_product* product() const { return GetRule<Rule_product>(0); }

};

class Rule_product: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PRODUCT; }

public:
	ParserGenerator::TokenNode* STAR() const { return GetToken(ETokenType::STAR, 0); }
	Rule_constant* constant() const { return GetRule<Rule_constant>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

};

class Rule_subtract: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::SUBTRACT; }

public:
	ParserGenerator::TokenNode* MINUS() const { return GetToken(ETokenType::MINUS, 0); }
	Rule_additive* additive() const { return GetRule<Rule_additive>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

};

class Rule_sum: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::SUM; }

public:
	ParserGenerator::TokenNode* STAR() const { return GetToken(ETokenType::STAR, 0); }
	Rule_additive* additive() const { return GetRule<Rule_additive>(0); }
	Rule_multiplicative* multiplicative() const { return GetRule<Rule_multiplicative>(0); }

};
