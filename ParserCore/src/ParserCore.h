#pragma once

// For use by Client Applications only

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ParseTree/RuleNode.h"
#include "Parser/ParseTree/TokenNode.h"
#include "Parser/Visitor.h"

#include "ParserTypes.h"

#include "App.h"

namespace PC = ParserCore;
namespace PCA = ParserCore::Automaton; 
namespace PCT = ParserCore::ParseTable;