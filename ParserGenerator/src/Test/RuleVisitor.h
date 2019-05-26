#pragma once

#include <string>
#include <vector>
#include <set>

#include "TestVisitorBase.h"
#include "../Parser/ParserConfig.h"

class RuleVisitor : public TestVisitorBase<std::set<std::vector<std::string>>>
{
protected:
	// Content -> Name
	std::map<std::string, std::string> m_LiteralMap;

public:
	virtual std::set<std::vector<std::string>> VisitRule_parseror(Rule_parseror* Context) override;
	virtual std::set<std::vector<std::string>> VisitRule_parseror2(Rule_parseror2* Context) override;
	virtual std::set<std::vector<std::string>> VisitRule_parserlist(Rule_parserlist* Context) override;
	virtual std::set<std::vector<std::string>> VisitRule_parserconst(Rule_parserconst* Context) override;
};

