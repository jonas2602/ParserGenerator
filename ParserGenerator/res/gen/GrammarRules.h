// Automatically generated File
#pragma once

#include "GrammarAlphabet.h"
#include <ParserCore.h>
class Rule_action;
class Rule_lexerconst;
class Rule_lexeror;
class Rule_lexeror2;
class Rule_lexerrule;
class Rule_operatorr;
class Rule_operatorr2;
class Rule_parserconst;
class Rule_parserlist;
class Rule_parseror;
class Rule_parseror2;
class Rule_parserrule;
class Rule_regex;
class Rule_rulelist;

class Rule_action: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::ACTION; }

public:
	PC::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }
	PC::TokenNode* ARROW() const { return GetToken(ETokenType::ARROW, 0); }

};

class Rule_lexerconst: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXERCONST; }

public:
	PC::TokenNode* RP() const { return GetToken(ETokenType::RP, 0); }
	PC::TokenNode* DOT() const { return GetToken(ETokenType::DOT, 0); }
	PC::TokenNode* LP() const { return GetToken(ETokenType::LP, 0); }
	PC::TokenNode* CHARSET() const { return GetToken(ETokenType::CHARSET, 0); }
	PC::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	PC::TokenNode* LITERAL() const { return GetToken(ETokenType::LITERAL, 0); }
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }

};

class Rule_lexeror: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXEROR; }

public:
	Rule_operatorr* operatorr() const { return GetRule<Rule_operatorr>(0); }
	Rule_lexeror2* lexeror2() const { return GetRule<Rule_lexeror2>(0); }

};

class Rule_lexeror2: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXEROR2; }

public:
	PC::TokenNode* PIPE() const { return GetToken(ETokenType::PIPE, 0); }
	Rule_operatorr* operatorr() const { return GetRule<Rule_operatorr>(0); }
	Rule_lexeror2* lexeror2() const { return GetRule<Rule_lexeror2>(0); }

};

class Rule_lexerrule: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::LEXERRULE; }

public:
	PC::TokenNode* SEMICOLON() const { return GetToken(ETokenType::SEMICOLON, 0); }
	PC::TokenNode* COLON() const { return GetToken(ETokenType::COLON, 0); }
	PC::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }
	Rule_action* action() const { return GetRule<Rule_action>(0); }

};

class Rule_operatorr: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::OPERATORR; }

public:
	Rule_operatorr2* operatorr2() const { return GetRule<Rule_operatorr2>(0); }
	Rule_lexerconst* lexerconst() const { return GetRule<Rule_lexerconst>(0); }

};

class Rule_operatorr2: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::OPERATORR2; }

public:
	PC::TokenNode* PLUS() const { return GetToken(ETokenType::PLUS, 0); }
	PC::TokenNode* QUESTIONMARK() const { return GetToken(ETokenType::QUESTIONMARK, 0); }
	PC::TokenNode* STAR() const { return GetToken(ETokenType::STAR, 0); }

};

class Rule_parserconst: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERCONST; }

public:
	PC::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }
	PC::TokenNode* RP() const { return GetToken(ETokenType::RP, 0); }
	PC::TokenNode* LP() const { return GetToken(ETokenType::LP, 0); }
	PC::TokenNode* LEXERID() const { return GetToken(ETokenType::LEXERID, 0); }
	PC::TokenNode* LITERAL() const { return GetToken(ETokenType::LITERAL, 0); }
	Rule_parseror* parseror() const { return GetRule<Rule_parseror>(0); }

};

class Rule_parserlist: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERLIST; }

public:
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }
	Rule_parserconst* parserconst() const { return GetRule<Rule_parserconst>(0); }

};

class Rule_parseror: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSEROR; }

public:
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() const { return GetRule<Rule_parseror2>(0); }

};

class Rule_parseror2: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSEROR2; }

public:
	PC::TokenNode* PIPE() const { return GetToken(ETokenType::PIPE, 0); }
	Rule_parserlist* parserlist() const { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() const { return GetRule<Rule_parseror2>(0); }

};

class Rule_parserrule: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::PARSERRULE; }

public:
	PC::TokenNode* PARSERID() const { return GetToken(ETokenType::PARSERID, 0); }
	PC::TokenNode* SEMICOLON() const { return GetToken(ETokenType::SEMICOLON, 0); }
	PC::TokenNode* COLON() const { return GetToken(ETokenType::COLON, 0); }
	Rule_parseror* parseror() const { return GetRule<Rule_parseror>(0); }

};

class Rule_regex: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::REGEX; }

public:
	Rule_regex* regex() const { return GetRule<Rule_regex>(0); }
	Rule_lexeror* lexeror() const { return GetRule<Rule_lexeror>(0); }

};

class Rule_rulelist: public PC::RuleNode
{
public:
	virtual int GetRuleType() const override { return ERuleType::RULELIST; }

public:
	Rule_parserrule* parserrule() const { return GetRule<Rule_parserrule>(0); }
	Rule_lexerrule* lexerrule() const { return GetRule<Rule_lexerrule>(0); }
	Rule_rulelist* rulelist() const { return GetRule<Rule_rulelist>(0); }

};
