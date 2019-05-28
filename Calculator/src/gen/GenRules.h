// Automatically generated File
#pragma once

#include "GenAlphabet.h"
#include <Parser.h>
class Rule_action;
class Rule_lexerconst;
class Rule_lexeror;
class Rule_lexeror2;
class Rule_lexerrule;
class Rule_operator;
class Rule_operator2;
class Rule_parserconst;
class Rule_parserlist;
class Rule_parseror;
class Rule_parseror2;
class Rule_parserrule;
class Rule_regex;
class Rule_rulelist;

class Rule_action: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::ACTION; }

public:
	ParserGenerator::TokenNode* ARROW() const { return GetToken(ETokenType::ARROW, 0); }
	ParserGenerator::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }

};

class Rule_lexerconst: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXERCONST; }

public:
	ParserGenerator::TokenNode* CHARSET() const { return GetToken(ETokenType::CHARSET, 0); }
	ParserGenerator::TokenNode* DOT() const { return GetToken(ETokenType::DOT, 0); }
	ParserGenerator::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	ParserGenerator::TokenNode* LITERAL() const { return GetToken(ETokenType::LITERAL, 0); }
	ParserGenerator::TokenNode* LP() const { return GetToken(ETokenType::LP, 0); }
	ParserGenerator::TokenNode* RP() const { return GetToken(ETokenType::RP, 0); }
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }

};

class Rule_lexeror: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXEROR; }

public:
	Rule_lexeror2* lexeror2() const { return GetRule<Rule_lexeror2>(0); }
	Rule_operator* operator() const { return GetRule<Rule_operator>(0); }

};

class Rule_lexeror2: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXEROR2; }

public:
	ParserGenerator::TokenNode* PIPE() const { return GetToken(ETokenType::PIPE, 0); }
	Rule_lexeror2* lexeror2() const { return GetRule<Rule_lexeror2>(0); }
	Rule_operator* operator() const { return GetRule<Rule_operator>(0); }

};

class Rule_lexerrule: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXERRULE; }

public:
	ParserGenerator::TokenNode* COLON() const { return GetToken(ETokenType::COLON, 0); }
	ParserGenerator::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	ParserGenerator::TokenNode* SEMICOLON() const { return GetToken(ETokenType::SEMICOLON, 0); }
	Rule_action* action() const { return GetRule<Rule_action>(0); }
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }

};

class Rule_operator: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::OPERATOR; }

public:
	Rule_lexerconst* lexerconst() const { return GetRule<Rule_lexerconst>(0); }
	Rule_operator2* operator2() const { return GetRule<Rule_operator2>(0); }

};

class Rule_operator2: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::OPERATOR2; }

public:
	ParserGenerator::TokenNode* PLUS() const { return GetToken(ETokenType::PLUS, 0); }
	ParserGenerator::TokenNode* QUESTIONMARK() const { return GetToken(ETokenType::QUESTIONMARK, 0); }
	ParserGenerator::TokenNode* STAR() const { return GetToken(ETokenType::STAR, 0); }

};

class Rule_parserconst: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERCONST; }

public:
	ParserGenerator::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	ParserGenerator::TokenNode* LITERAL() const { return GetToken(ETokenType::LITERAL, 0); }
	ParserGenerator::TokenNode* LP() const { return GetToken(ETokenType::LP, 0); }
	ParserGenerator::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }
	ParserGenerator::TokenNode* RP() const { return GetToken(ETokenType::RP, 0); }
	Rule_parseror* parseror() const { return GetRule<Rule_parseror>(0); }

};

class Rule_parserlist: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERLIST; }

public:
	Rule_parserconst* parserconst() const { return GetRule<Rule_parserconst>(0); }
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }

};

class Rule_parseror: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSEROR; }

public:
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() const { return GetRule<Rule_parseror2>(0); }

};

class Rule_parseror2: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSEROR2; }

public:
	ParserGenerator::TokenNode* PIPE() const { return GetToken(ETokenType::PIPE, 0); }
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() const { return GetRule<Rule_parseror2>(0); }

};

class Rule_parserrule: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERRULE; }

public:
	ParserGenerator::TokenNode* COLON() const { return GetToken(ETokenType::COLON, 0); }
	ParserGenerator::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }
	ParserGenerator::TokenNode* SEMICOLON() const { return GetToken(ETokenType::SEMICOLON, 0); }
	Rule_parseror* parseror() const { return GetRule<Rule_parseror>(0); }

};

class Rule_regex: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::REGEX; }

public:
	Rule_lexeror* lexeror() const { return GetRule<Rule_lexeror>(0); }
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }

};

class Rule_rulelist: public ParserGenerator::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::RULELIST; }

public:
	Rule_lexerrule* lexerrule() const { return GetRule<Rule_lexerrule>(0); }
	Rule_parserrule* parserrule() const { return GetRule<Rule_parserrule>(0); }
	Rule_rulelist* rulelist() const { return GetRule<Rule_rulelist>(0); }

};
