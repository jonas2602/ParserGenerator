#pragma once

// For use by Client Applications only

#include "ParserCore/Lexer/Lexer.h"
#include "ParserCore/Parser/Parser.h"
#include "ParserCore/Parser/ParseTree/RuleNode.h"
#include "ParserCore/Parser/ParseTree/TokenNode.h"
#include "ParserCore/Parser/Visitor.h"

#include "ParserCore/ParserTypes.h"

namespace PC = ParserCore;
namespace PCA = ParserCore::Automaton; 
namespace PCT = ParserCore::ParseTable;