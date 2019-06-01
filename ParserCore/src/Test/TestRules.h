#pragma once

#include "../Parser/ParseTree/RuleNode.h"
#include "TestAlphabet.h"

class Rule_rulelist;

class Rule_parserrule;
class Rule_parseror;
class Rule_parseror2;
class Rule_parserlist;
class Rule_parserconst;

class Rule_lexerrule;
class Rule_action;
class Rule_regex;
class Rule_lexeror;
class Rule_lexeror2;
class Rule_operator;
class Rule_operator2;
class Rule_anytime;
class Rule_once;
class Rule_optional;
class Rule_lexerconst;

class Rule_rulelist : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::RULELIST; }

public:
	Rule_parserrule* parserrule() { return GetRule<Rule_parserrule>(0); }
	Rule_lexerrule* lexerrule() { return GetRule<Rule_lexerrule>(0); }
	Rule_rulelist* rulelist() { return GetRule<Rule_rulelist>(0); }
};

class Rule_parserrule : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERRULE; }

public:
	ParserCore::TokenNode* PARSERID() { return GetToken(ETokenType::PARSERID, 0); }
	ParserCore::TokenNode* COLON() { return GetToken(ETokenType::COLON, 0); }
	Rule_parseror* parseror() { return GetRule<Rule_parseror>(0); }
	ParserCore::TokenNode* SEMICOLON() { return GetToken(ETokenType::SEMICOLON, 0); }
};

class Rule_parseror : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSEROR; }

public:
	Rule_parserlist* parserlist() { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() { return GetRule<Rule_parseror2>(0); }
};

class Rule_parseror2 : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSEROR2; }

public:
	ParserCore::TokenNode* PIPE() { return GetToken(ETokenType::PIPE, 0); }
	Rule_parserlist* parserlist() { return GetRule<Rule_parserlist>(0); }
	Rule_parseror2* parseror2() { return GetRule<Rule_parseror2>(0); }

};

class Rule_parserlist : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERLIST; }

public:
	Rule_parserconst* parserconst() { return GetRule<Rule_parserconst>(0); }
	Rule_parserlist* parserlist() { return GetRule<Rule_parserlist>(0); }

};

class Rule_parserconst : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::PARSERCONST; }

public:
	ParserCore::TokenNode* LEXERID() { return GetToken(ETokenType::LEXERID, 0); }
	ParserCore::TokenNode* PARSERID() { return GetToken(ETokenType::PARSERID, 0); }
	ParserCore::TokenNode* LITERAL() { return GetToken(ETokenType::LITERAL, 0); }
	ParserCore::TokenNode* LEFTPARENTHESE() { return GetToken(ETokenType::LEFTPARENTHESE, 0); }
	Rule_parseror* parseror() { return GetRule<Rule_parseror>(0); }
	ParserCore::TokenNode* RIGHTPARENTHESE() { return GetToken(ETokenType::RIGHTPARENTHESE, 0); }

};


class Rule_lexerrule : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::LEXERRULE; }

public:
	ParserCore::TokenNode* LEXERID() { return GetToken(ETokenType::LEXERID, 0); }
	ParserCore::TokenNode* COLON() { return GetToken(ETokenType::COLON, 0); }
	Rule_regex* regex() { return GetRule<Rule_regex>(0); }	
	Rule_action* action() { return GetRule<Rule_action>(0); }
	ParserCore::TokenNode* SEMICOLON() { return GetToken(ETokenType::SEMICOLON, 0); }

};


class Rule_action : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::ACTION; }

public:
	ParserCore::TokenNode* ARROW() { return GetToken(ETokenType::ARROW, 0); }
	ParserCore::TokenNode* PARSERID() { return GetToken(ETokenType::PARSERID, 0); }

};


class Rule_regex : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::REGEX; }

public:
	Rule_lexeror* lexeror() { return GetRule<Rule_lexeror>(0); }
	Rule_regex* regex() { return GetRule<Rule_regex>(0); }

};

class Rule_lexeror : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::LEXEROR; }

public:
	Rule_operator* operatorr() { return GetRule<Rule_operator>(0); }
	Rule_lexeror2* lexeror2() { return GetRule<Rule_lexeror2>(0); }

};


class Rule_lexeror2 : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::LEXEROR2; }

public:
	ParserCore::TokenNode* PIPE() { return GetToken(ETokenType::PIPE, 0); }
	Rule_operator* operatorr() { return GetRule<Rule_operator>(0); }
	Rule_lexeror2* lexeror2() { return GetRule<Rule_lexeror2>(0); }

};


class Rule_operator : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::OPERATOR; }

public:
	Rule_lexerconst* lexerconst() { return GetRule<Rule_lexerconst>(0); }
	Rule_operator2* operator2() { return GetRule<Rule_operator2>(0); }
	
};


class Rule_operator2 : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::OPERATOR2; }

public:
	ParserCore::TokenNode* STAR() { return GetToken(ETokenType::STAR, 0); }
	ParserCore::TokenNode* PLUS() { return GetToken(ETokenType::PLUS, 0); }
	ParserCore::TokenNode* QUESTIONMARK() { return GetToken(ETokenType::QUESTIONMARK, 0); }

};


class Rule_lexerconst : public ParserCore::RuleNode
{
public:
	// Inherited via RuleNode
	virtual int GetRuleType() const override { return ERuleType::LEXERCONST; }

public:
	ParserCore::TokenNode* LEFTPARENTHESE() { return GetToken(ETokenType::LEFTPARENTHESE, 0); }
	Rule_regex* regex() { return GetRule<Rule_regex>(0); }
	ParserCore::TokenNode* RIGHTPARENTHESE() { return GetToken(ETokenType::RIGHTPARENTHESE, 0); }
	ParserCore::TokenNode* LEXERID() { return GetToken(ETokenType::LEXERID, 0); }
	ParserCore::TokenNode* DOT() { return GetToken(ETokenType::DOT, 0); }
	ParserCore::TokenNode* CHARSET() { return GetToken(ETokenType::CHARSET, 0); }
	ParserCore::TokenNode* LITERAL() { return GetToken(ETokenType::LITERAL, 0); }

};