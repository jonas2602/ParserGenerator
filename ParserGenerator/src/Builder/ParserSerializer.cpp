#include "ParserSerializer.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "../ParserTypes.h"
#include "../Generator/Snippets/FunctionSnippet.h"
#include "../Generator/Snippets/ForwardDeclSnippet.h"
#include "../Generator/Snippets/ClassSnippet.h"
#include "../Generator/Snippets/ConstructorSnippet.h"
#include "../Generator/Snippets/SwitchSnippet.h"

#include "../Utils/StringUtils.h"

namespace ParserGenerator {
	ParserSerializer::ParserSerializer(const std::string& InDirPath, const std::string& InParserName, const std::string& InCodePath, const std::string& InDocuPath)
		: m_DirPath(InDirPath), m_ParserName(InParserName), m_CodePath(InCodePath), m_DocuPath(InDocuPath)
	{
		m_Generator = new CodeGenerator(InDirPath);
	}

	bool ParserSerializer::WriteAlphabetDoc(Alphabet* InAlphabet) const
	{
		// Create Output Streams
		std::stringstream TokenStream;
		ParserSerializer::WriteTokenList(InAlphabet, TokenStream);
		std::stringstream NonTerminalStream;
		ParserSerializer::WriteNonTerminalList(InAlphabet, NonTerminalStream);

		// Create File
		std::string FileName = ExtendFileName("Alphabet");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream();
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << NonTerminalStream.str();
		OutStream << std::endl;

		return true;
	}



	bool ParserSerializer::WriteParsingTableDoc(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create Output Streams
		std::stringstream TokenStream;
		ParserSerializer::WriteTokenList(InAlphabet, TokenStream);
		std::stringstream NonTerminalStream;
		ParserSerializer::WriteNonTerminalList(InAlphabet, NonTerminalStream);
		std::stringstream TableStream;
		std::stringstream RuleStream;

		// Write Rules
		for (ParserConfigElement* Production : ParsConfig->GetProductionList())
		{
			RuleStream << Production->m_LocalRuleIndex << " " << Production->m_NonTerminal << "(" << InAlphabet->GetNonTerminalIndex(Production->m_NonTerminal) << ") ->";
			for (const std::string& TokenClass : Production->m_TokenClasses)
			{
				int ElementIndex = -1;
				if (InAlphabet->IsNonTerminal(TokenClass)) ElementIndex = InAlphabet->GetNonTerminalIndex(TokenClass);
				else if (InAlphabet->IsToken(TokenClass)) ElementIndex = InAlphabet->GetTokenIndex(TokenClass);

				const std::string& ElementName = IsEpsilon(TokenClass) ? "EPSILON" : TokenClass;

				RuleStream << " " << ElementName << "(" << ElementIndex << ")";
			}

			RuleStream << std::endl;
		}

		// Write ParseTable
		for (const std::pair<int, std::map<int, int>>& NonTerminalPair : InTable->GetProductionMap())
		{
			for (const std::pair<int, int>& TokenPair : NonTerminalPair.second)
			{
				const std::string& NonTerminalName = InAlphabet->GetNonTerminalName(NonTerminalPair.first);
				const std::string& TokenName = InAlphabet->GetTokenName(TokenPair.first);

				const std::vector<std::string>& RuleElementList = ParsConfig->GetRuleElements(NonTerminalName, TokenPair.second);
				TableStream << "[" << NonTerminalName << "(" << NonTerminalPair.first << "), " << TokenName << "(" << TokenPair.first << ")] -> " << TokenPair.second;

				for (const std::string& RuleElement : RuleElementList)
				{
					TableStream << " " << (IsEpsilon(RuleElement) ? "EPSILON" : RuleElement);
				}

				TableStream << std::endl;
			}
		}

		// Table that is used in Parser
		std::string TableString;
		ParserSerializer::SerializeParsingTable(InTable, TableString);


		// Create File
		std::string FileName = ExtendFileName("ParsingTable");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream();
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Avaliable Non Terminals:" << std::endl << "[Index] [Name]" << std::endl;
		OutStream << NonTerminalStream.str();
		OutStream << std::endl;
		OutStream << "Table Entries:" << std::endl << "([NonTerminal], [Token]) -> [Rule]" << std::endl;
		OutStream << TableStream.str();
		OutStream << std::endl;
		OutStream << "Rules:" << std::endl << "[LocalRuleIndex] [NonTerminal] -> [Element] [Element] ..." << std::endl;
		OutStream << RuleStream.str();
		OutStream << std::endl;
		OutStream << "Serialized Parsing Table:" << std::endl << "[NonTerminal] [Token] [LocalRuleIndex] ..." << std::endl;
		OutStream << TableString;

		return true;
	}

	bool ParserSerializer::WriteAutomatonDoc(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet)
	{
		// Create Output Streams
		std::stringstream TokenStream;
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		// Write Token Data
		int TokenIndex = 0;
		for (const LexerConfigElement& TokenType : LexConfig->GetRegexList())
		{
			TokenStream << TokenIndex++ << " " << TokenType.m_Name << " " << TokenType.m_Action << std::endl;
		}

		std::map<Automaton::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, Automaton::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			Automaton::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << ActiveIndex << " " << ActiveState->GetName() << " " << ActiveState->GetStatePriority() << std::endl;

			// Write Transition Data
			for (Automaton::Transition* Trans : ActiveState->GetTransitions())
			{
				Automaton::State* OtherState = Trans->GetTargetState();
				int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = StateIndex++;
				TransitionStream << ActiveIndex << " " << OtherIndex;

				// Write Condition Data
				for (const char& Symbol : Trans->GetCondition())
				{
					TransitionStream << " " << (int)Symbol;
				}

				TransitionStream << std::endl;
			}
		}

		const std::string& StartStateName = InDFA->GetStartState()->GetName();
		int StartStateIndex = IndexMap[InDFA->GetStartState()];

		// Table that is used in Parser
		std::string AutomatonString;
		ParserSerializer::SerializeAutomaton(InDFA, AutomatonString);

		// Create File
		std::string FileName = ExtendFileName("Automaton");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_DocuPath);
		CodeSnippet_Plain* PlainSnippet = new CodeSnippet_Plain();
		AlphabetFile->AddSnippet(PlainSnippet);

		// Write Content to Snippet
		std::stringstream& OutStream = PlainSnippet->GetTextStream();
		OutStream << "Avaliable Tokens:" << std::endl << "[Index] [Name] [Action]" << std::endl;
		OutStream << TokenStream.str();
		OutStream << std::endl;
		OutStream << "Automaton States:" << std::endl << "[Index] [Symbolic Name] [Priority]" << std::endl;
		OutStream << StateStream.str();
		OutStream << std::endl;
		OutStream << "Automaton Transitions:" << std::endl << "[Start State] [End State] [Condition chars]" << std::endl;
		OutStream << TransitionStream.str();
		OutStream << std::endl;
		OutStream << "Automaton Start State:" << std::endl << "[Index] [Symbolic Name]" << std::endl;
		OutStream << StartStateIndex << " " << StartStateName << std::endl;
		OutStream << std::endl;
		OutStream << "Serialized Deterministic Finite Automaton:" << std::endl;
		OutStream << AutomatonString;

		return true;
	}

	bool ParserSerializer::SerializeParsingTable(ParseTable::ParsingTable* InTable, std::string& OutString)
	{
		std::stringstream OutStream;

		for (const std::pair<int, std::map<int, int>>& NonTerminalPair : InTable->GetProductionMap())
		{
			for (const std::pair<int, int>& TokenPair : NonTerminalPair.second)
			{
				// List of tripples (nonterminal, token, localruleindex)
				OutStream << NonTerminalPair.first << " " << TokenPair.first << " " << TokenPair.second << " ";
			}
		}

		OutString = OutStream.str();
		return true;
	}

	bool ParserSerializer::SerializeAutomaton(Automaton::DFA* InDFA, std::string& OutString)
	{
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		std::map<Automaton::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, Automaton::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			Automaton::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << " " << ActiveIndex << " " << ActiveState->GetStatePriority();

			// Write Transition Data
			for (Automaton::Transition* Trans : ActiveState->GetTransitions())
			{
				Automaton::State* OtherState = Trans->GetTargetState();
				int OtherIndex = IndexMap.find(OtherState) != IndexMap.end() ? IndexMap[OtherState] : IndexMap[OtherState] = StateIndex++;
				TransitionStream << ActiveIndex << " " << OtherIndex;

				// Write Condition Data
				for (const char& Symbol : Trans->GetCondition())
				{
					TransitionStream << " " << (int)Symbol;
				}

				TransitionStream << "\\n";
			}
		}

		// start state
		int StartIndex = IndexMap[InDFA->GetStartState()];

		OutString = std::to_string(StartIndex) + StateStream.str() + "\\n" + TransitionStream.str();
		return true;
	}

	bool ParserSerializer::WriteAlphabetCode(Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Alphabet");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);

		// Add Enums
		AlphabetFile->AddSnippet(new CodeSnippet_Enum("ETokenType", InAlphabet->GetTokenMap()));
		AlphabetFile->AddSnippet(new CodeSnippet_Enum("ERuleType", InAlphabet->GetNonTerminalMap()));

		return true;
	}

	bool ParserSerializer::WriteRuleCode(ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Rules");
		FileTemplate* RuleFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);

		// Add Includes
		RuleFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Alphabet") + ".h"));
		RuleFile->AddSnippet(new CodeSnippet_Include("Parser.h", false));

		for (const std::string& NonTerminal : ParsConfig->GetNonTerminals())
		{
			CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class("Rule_" + NonTerminal, "ParserGenerator::RuleNode");
			RuleFile->AddSnippet(ClassSnippet);
			RuleFile->AddSnippet(new CodeSnippet_ForwardDecl("class", "Rule_" + NonTerminal));

			ClassSnippet->CreateNewGroup("public");
			std::string UpperCaseName = StringUtils::ToUpperCase(NonTerminal);
			ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetRuleType", { "return ERuleType::" + UpperCaseName + ";" }, "int", { CONSTANT, OVERRIDE, VIRTUAL, SINGLELINE, HEADERDEFINITION }));

			ClassSnippet->CreateNewGroup("public");

			std::set<std::string> TokenClasses;
			std::set<std::string> NonTerminalClasses;

			for (ParserConfigElement* Production : ParsConfig->GetAllProductionsForNonTerminal(NonTerminal))
			{
				for (const std::string& Element : Production->m_TokenClasses)
				{
					// Ignore Epsilon
					if (IsEpsilon(Element)) continue;

					if (ParsConfig->IsNonTerminal(Element))
					{
						NonTerminalClasses.insert(Element);
					}
					else
					{
						TokenClasses.insert(Element);
					}
				}
			}

			for (const std::string& TokenName : TokenClasses)
			{
				std::string UpperCaseName = StringUtils::ToUpperCase(TokenName);
				ClassSnippet->AttachSnippet(new CodeSnippet_Function(UpperCaseName, { "return GetToken(ETokenType::" + UpperCaseName + ", 0);" }, "ParserGenerator::TokenNode*", { CONSTANT, SINGLELINE, HEADERDEFINITION }));
			}

			for (const std::string& NonTerminalName : NonTerminalClasses)
			{
				std::string RuleName = "Rule_" + NonTerminalName;
				ClassSnippet->AttachSnippet(new CodeSnippet_Function(NonTerminalName, { "return GetRule<" + RuleName + ">(0);" }, RuleName + "*", { CONSTANT, SINGLELINE, HEADERDEFINITION }));
			}
		}

		return true;
	}

	bool ParserSerializer::WriteLexerCode(Automaton::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Lexer");
		FileTemplate* LexerFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);

		// Add Includes
		LexerFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Alphabet") + ".h"));
		LexerFile->AddSnippet(new CodeSnippet_Include("Parser.h", false));

		// Add Lexer Class
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "ParserGenerator::Lexer");
		LexerFile->AddSnippet(ClassSnippet);

		// Add Constructor
		ClassSnippet->CreateNewGroup("public");
		ClassSnippet->AttachSnippet(new CodeSnippet_Constructor({ "Init();" }, { "const std::string& InSourceCode" }, { {"Lexer","InSourceCode" } }));

		// Add Serialized Automaton
		ClassSnippet->CreateNewGroup("protected");
		std::string AutomatonString;
		ParserSerializer::SerializeAutomaton(InDFA, AutomatonString);
		ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetSerializedAutomaton", { "return \"" + AutomatonString + "\";" }, "const char*", { CONSTANT, VIRTUAL, OVERRIDE }));

		// Add Skipped TokenTypes
		std::string HiddenList = "{ ";
		for (const LexerConfigElement& Regex : LexConfig->GetRegexList())
		{
			if (Regex.m_Action == ELexerAction::SKIP)
			{
				HiddenList += "ETokenType::" + Regex.m_Name + ", ";
			}
		}
		HiddenList += "}";
		ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetHiddenTokenTypes", { "return " + HiddenList + ";" }, "std::set<int>", { CONSTANT, VIRTUAL, OVERRIDE }));

		return true;
	}

	bool ParserSerializer::WriteParserCode(ParseTable::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Parser");
		FileTemplate* ParserFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);

		// Add Includes
		ParserFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Rules") + ".h"));
		ParserFile->AddSnippet(new CodeSnippet_Include("Parser.h", false));

		// Add Parser Class
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "ParserGenerator::Parser");
		ParserFile->AddSnippet(ClassSnippet);

		// Add Constructor
		ClassSnippet->CreateNewGroup("public");
		std::string AutomatonString;
		ClassSnippet->AttachSnippet(new CodeSnippet_Constructor({ "LoadParsingTable();" }, { "const std::vector<ParserGenerator::Token*>& TokenStream" }, { {"Parser", "TokenStream" } }));

		// Add Parsing Rules
		ClassSnippet->CreateNewGroup("public");
		for (const std::string& NonTerminal : ParsConfig->GetNonTerminals())
		{
			std::string FunctionName = NonTerminal;
			FunctionName[0] = toupper(FunctionName[0]);
			std::string RuleName = "Rule_" + NonTerminal;

			std::vector<std::string> BodyLines;
			BodyLines.insert(BodyLines.end(), {
				"OutRule = new " + RuleName + "();",
				"EnterRule(OutRule);",
				"",
				});

			std::vector<ParserConfigElement*> NonTerminalRules = ParsConfig->GetAllProductionsForNonTerminal(NonTerminal);
			if (NonTerminalRules.size() == 1)
			{
				for (const std::string& Element : NonTerminalRules[0]->m_TokenClasses)
				{
					if (ParsConfig->IsNonTerminal(Element))
					{
						std::string ElementFunctionName = Element;
						ElementFunctionName[0] = toupper(ElementFunctionName[0]);
						std::string ElementRuleName = "Rule_" + Element;
						BodyLines.push_back("CALL_CHILD(" + ElementFunctionName + ", " + ElementRuleName + ");");
					}
					else
					{
						std::string ElementTokenName = StringUtils::ToUpperCase(Element);
						BodyLines.push_back("TRY_MATCH(ETokenType::" + ElementTokenName + ");");
					}
				}
			}
			else
			{
				CodeSnippet_Switch* SwitchSnippet = new CodeSnippet_Switch("PredictProduction()");
				for (ParserConfigElement* Rule : NonTerminalRules)
				{
					std::vector<std::string> CaseLines;
					for (const std::string& Element : Rule->m_TokenClasses)
					{
						if (IsEpsilon(Element))
						{
							CaseLines.push_back("// EPSILON");
						}
						else if (ParsConfig->IsNonTerminal(Element))
						{
							std::string ElementFunctionName = Element;
							ElementFunctionName[0] = toupper(ElementFunctionName[0]);
							std::string ElementRuleName = "Rule_" + Element;
							CaseLines.push_back("CALL_CHILD(" + ElementFunctionName + ", " + ElementRuleName + ");");
						}
						else
						{
							std::string ElementTokenName = StringUtils::ToUpperCase(Element);
							CaseLines.push_back("TRY_MATCH(ETokenType::" + ElementTokenName + ");");
						}
					}

					SwitchSnippet->AddCase(std::to_string(Rule->m_LocalRuleIndex), CaseLines);
				}

				std::vector<std::string> RawSwitchLines = SwitchSnippet->GetRawLines();
				BodyLines.insert(BodyLines.end(), RawSwitchLines.begin(), RawSwitchLines.end());
			}

			BodyLines.insert(BodyLines.end(), {
				"",
				"ExitRule(OutRule);",
				"return true;"
				});

			ClassSnippet->AttachSnippet(new CodeSnippet_Function(FunctionName, BodyLines, { RuleName + "*& OutRule" }, "bool"));
			// bool Rulelist(Rule_rulelist * &OutRule);
		}

		// Add Serialized ParsingTable
		ClassSnippet->CreateNewGroup("protected");
		std::string TableString;
		ParserSerializer::SerializeParsingTable(InTable, TableString);
		ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetSerializedTable", { "return \"" + TableString + "\";" }, "const char*", { CONSTANT, VIRTUAL, OVERRIDE }));

		return false;
	}

	bool ParserSerializer::WriteVisitorCode(ParserConfig* ParsConfig) const
	{
		// Create File
		std::string FileName = ExtendFileName("VisitorBase");
		FileTemplate* VisitorFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);

		// Add Includes
		VisitorFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Rules") + ".h"));
		VisitorFile->AddSnippet(new CodeSnippet_Include("Parser.h", false));

		// Add Visitor BaseClass
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "ParserGenerator::Visitor<T>");
		VisitorFile->AddSnippet(ClassSnippet);
		ClassSnippet->AddTemplating({ "T" });

		// Add virtual Visit Functions
		ClassSnippet->CreateNewGroup("public");
		for (const std::string& NonTerminal : ParsConfig->GetNonTerminals())
		{
			std::string FunctionName = "VisitRule_" + NonTerminal;
			std::string RuleName = "Rule_" + NonTerminal;
			ClassSnippet->AttachSnippet(new CodeSnippet_Function(FunctionName, { "return T();" }, { RuleName + "* Context" }, "T", { VIRTUAL, SINGLELINE, HEADERDEFINITION }));
		}

		// Add Templated visit "caller"
		ClassSnippet->CreateNewGroup("public");
		CodeSnippet_Function* VisitTemplate = new CodeSnippet_Function("Visit", { "static_assert(false);" }, { "U* Context" }, "T", { HEADERDEFINITION });
		ClassSnippet->AttachSnippet(VisitTemplate);
		VisitTemplate->AddTemplating({ "U" });

		for (const std::string& NonTerminal : ParsConfig->GetNonTerminals())
		{
			std::string FunctionName = "VisitRule_" + NonTerminal;
			std::string RuleName = "Rule_" + NonTerminal;
			ClassSnippet->AttachSnippet(new CodeSnippet_Function("Visit<" + RuleName + ">", { "return " + FunctionName + "(Context);" }, { RuleName + "* Context" }, "T", { TEMPLATE, SINGLELINE, HEADERDEFINITION }));
		}

		return false;
	}

	void ParserSerializer::Finish() const
	{
		m_Generator->GenerateFiles();
	}

	void ParserSerializer::WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream)
	{
		const std::vector<std::string>& TokenList = InAlphabet->GetTokenList();
		for (int i = 0; i < TokenList.size(); i++)
		{
			TokenStream << i << " " << TokenList[i] << std::endl;
		}
	}

	void ParserSerializer::WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream)
	{
		const std::vector<std::string>& NonTerminalList = InAlphabet->GetNonTerminalList();
		for (int i = 0; i < NonTerminalList.size(); i++)
		{
			NonTerminalStream << i << " " << NonTerminalList[i] << std::endl;
		}
	}

	std::string ParserSerializer::ExtendFileName(const std::string& RawFileName) const
	{
		return m_ParserName + RawFileName;
	}

}