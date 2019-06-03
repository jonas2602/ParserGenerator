#include "ParserSerializer.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <ParserCore.h>
#include "../Serializer/Snippets/ClassSnippet.h"
#include "../Serializer/Snippets/ConstructorSnippet.h"
#include "../Serializer/Snippets/EnumSnippet.h"
#include "../Serializer/Snippets/ForwardDeclSnippet.h"
#include "../Serializer/Snippets/FunctionSnippet.h"
#include "../Serializer/Snippets/IncludeSnippet.h"
#include "../Serializer/Snippets/NamespaceSnippet.h"
#include "../Serializer/Snippets/PlainSnippet.h"
#include "../Serializer/Snippets/SwitchSnippet.h"


#include "../Utils/StringUtils.h"

namespace ParserGenerator {
	ParserSerializer::ParserSerializer(const std::string& InDirPath, const std::string& InParserName, const std::string& InNamespaceName, const std::string& InCodePath, const std::string& InDocuPath)
		: m_DirPath(InDirPath), m_ParserName(InParserName), m_NamespaceName(InNamespaceName), m_CodePath(InCodePath), m_DocuPath(InDocuPath)
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



	bool ParserSerializer::WriteParsingTableDoc(PCT::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create Output Streams
		std::stringstream TokenStream;
		ParserSerializer::WriteTokenList(InAlphabet, TokenStream);
		std::stringstream NonTerminalStream;
		ParserSerializer::WriteNonTerminalList(InAlphabet, NonTerminalStream);
		std::stringstream TableStream;
		std::stringstream RuleStream;

		// Write Rules
		for (RuleDefinition* Production : ParsConfig->GetProductionList())
		{
			RuleStream << Production->m_LocalRuleIndex << " " << Production->m_NonTerminal << "(" << InAlphabet->GetRuleIndex(Production->m_NonTerminal) << ") ->";
			for (RuleElement* Element : Production->m_RuleElements)
			{
				int ElementIndex = InAlphabet->GetElementIndex(Element);
				const std::string& ElementName = Element->GetDisplayName();
				RuleStream << " " << ElementName << "(" << ElementIndex << ")";
			}

			RuleStream << std::endl;
		}

		// Write ParseTable
		for (const std::pair<int, std::map<int, int>>& NonTerminalPair : InTable->GetProductionMap())
		{
			for (const std::pair<int, int>& TokenPair : NonTerminalPair.second)
			{
				const std::string& NonTerminalName = InAlphabet->GetRuleName(NonTerminalPair.first);
				const std::string& TokenName = InAlphabet->GetTokenName(TokenPair.first);

				const std::vector<RuleElement*>& RuleElementList = ParsConfig->GetRuleElements(NonTerminalName, TokenPair.second);
				TableStream << "[" << NonTerminalName << "(" << NonTerminalPair.first << "), " << TokenName << "(" << TokenPair.first << ")] -> " << TokenPair.second;

				for (RuleElement* Element : RuleElementList)
				{
					TableStream << " " << Element->GetDisplayName();
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

	bool ParserSerializer::WriteAutomatonDoc(PCA::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet)
	{
		// Create Output Streams
		std::stringstream TokenStream;
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		// Write Token Data
		int TokenIndex = 0;
		for (TokenDefinition* TokenType : LexConfig->GetRegexList())
		{
			TokenStream << TokenIndex++ << " " << TokenType->m_Name << " " << TokenType->m_Action << std::endl;
		}

		std::map<PCA::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, PCA::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			PCA::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << ActiveIndex << " " << ActiveState->GetName() << " " << ActiveState->GetStatePriority() << std::endl;

			// Write Transition Data
			for (PCA::Transition* Trans : ActiveState->GetTransitions())
			{
				PCA::State* OtherState = Trans->GetTargetState();
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

	bool ParserSerializer::WriteAlphabetCode(Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Alphabet");
		FileTemplate* AlphabetFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		std::vector<CodeSnippet_Base*> RootSnippets;
		// Add Enums
		RootSnippets.push_back(new CodeSnippet_Enum("ETokenType", InAlphabet->GetTokenIndexMap()));
		RootSnippets.push_back(new CodeSnippet_Enum("ERuleType", InAlphabet->GetRuleIndexMap()));

		if (m_NamespaceName.empty())
		{
			AlphabetFile->AddSnippet(RootSnippets);
		}
		else
		{
			CodeSnippet_Namespace* NamespaceSnippet = new CodeSnippet_Namespace(m_NamespaceName, false);
			AlphabetFile->AddSnippet(NamespaceSnippet);
			NamespaceSnippet->AttachSnippet(RootSnippets);
		}

		return true;
	}

	bool ParserSerializer::WriteRuleCode(ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Rules");
		FileTemplate* RuleFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		std::vector<CodeSnippet_Base*> RootSnippets;

		// Add Includes
		RuleFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Alphabet") + ".h"));
		RuleFile->AddSnippet(new CodeSnippet_Include("ParserCore.h", false));

		for (const std::string& NonTerminal : InAlphabet->GetNonTerminalNames())
		{
			CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class("Rule_" + NonTerminal, "PC::RuleNode");
			RootSnippets.push_back(ClassSnippet);
			RootSnippets.push_back(new CodeSnippet_ForwardDecl("class", "Rule_" + NonTerminal));

			ClassSnippet->CreateNewGroup("public");
			std::string UpperCaseName = StringUtils::ToUpperCase(NonTerminal);
			ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetRuleType", { "return ERuleType::" + UpperCaseName + ";" }, "int", { CONSTANT, OVERRIDE, VIRTUAL, SINGLELINE, HEADERDEFINITION }));

			ClassSnippet->CreateNewGroup("public");

			std::set<RuleElement*> TokenClasses;
			std::set<RuleElement*> NonTerminalClasses;

			for (RuleDefinition* Production : ParsConfig->GetAllProductionsForNonTerminal(NonTerminal))
			{
				for (RuleElement* Element : Production->m_RuleElements)
				{
					// Ignore Epsilon, EOF and Literals
					if (Element->IsEpsilon() || PC::IsEOS(Element->m_Content) || Element->m_Type == ERuleElementType::LITERAL) continue;

					if (Element->IsNonTerminal())
					{
						NonTerminalClasses.insert(Element);
					}
					else
					{
						TokenClasses.insert(Element);
					}
				}
			}

			for (RuleElement* Token : TokenClasses)
			{
				std::string UpperCaseName = StringUtils::ToUpperCase(Token->m_Content);
				ClassSnippet->AttachSnippet(new CodeSnippet_Function(UpperCaseName, { "return GetToken(ETokenType::" + UpperCaseName + ", 0);" }, "PC::TokenNode*", { CONSTANT, SINGLELINE, HEADERDEFINITION }));
			}

			for (RuleElement* NonTerminal : NonTerminalClasses)
			{
				std::string RuleName = "Rule_" + NonTerminal->m_Content;
				ClassSnippet->AttachSnippet(new CodeSnippet_Function(NonTerminal->m_Content, { "return GetRule<" + RuleName + ">(0);" }, RuleName + "*", { CONSTANT, SINGLELINE, HEADERDEFINITION }));
			}
		}

		if (m_NamespaceName.empty())
		{
			RuleFile->AddSnippet(RootSnippets);
		}
		else
		{
			CodeSnippet_Namespace* NamespaceSnippet = new CodeSnippet_Namespace(m_NamespaceName, false);
			RuleFile->AddSnippet(NamespaceSnippet);
			NamespaceSnippet->AttachSnippet(RootSnippets);
		}

		return true;
	}

	bool ParserSerializer::WriteLexerCode(PCA::DFA* InDFA, LexerConfig* LexConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Lexer");
		FileTemplate* LexerFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		std::vector<CodeSnippet_Base*> RootSnippets;

		// Add Includes
		LexerFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Alphabet") + ".h"));
		LexerFile->AddSnippet(new CodeSnippet_Include("ParserCore.h", false));

		// Add Lexer Class
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "PC::Lexer");
		RootSnippets.push_back(ClassSnippet);

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
		for (TokenDefinition* Regex : LexConfig->GetRegexList())
		{
			if (Regex->m_Action == ELexerAction::SKIP)
			{
				HiddenList += "ETokenType::" + Regex->m_Name + ", ";
			}
		}
		HiddenList += "}";
		ClassSnippet->AttachSnippet(new CodeSnippet_Function("GetHiddenTokenTypes", { "return " + HiddenList + ";" }, "std::set<int>", { CONSTANT, VIRTUAL, OVERRIDE }));

		if (m_NamespaceName.empty())
		{
			LexerFile->AddSnippet(RootSnippets);
		}
		else
		{
			CodeSnippet_Namespace* NamespaceSnippet = new CodeSnippet_Namespace(m_NamespaceName);
			LexerFile->AddSnippet(NamespaceSnippet);
			NamespaceSnippet->AttachSnippet(RootSnippets);
		}

		return true;
	}

	bool ParserSerializer::WriteParserCode(PCT::ParsingTable* InTable, ParserConfig* ParsConfig, Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("Parser");
		FileTemplate* ParserFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		std::vector<CodeSnippet_Base*> RootSnippets;

		// Add Includes
		ParserFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Rules") + ".h"));
		ParserFile->AddSnippet(new CodeSnippet_Include("ParserCore.h", false));

		// Add Parser Class
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "PC::Parser");
		RootSnippets.push_back(ClassSnippet);

		// Add Constructor
		ClassSnippet->CreateNewGroup("public");
		std::string AutomatonString;
		ClassSnippet->AttachSnippet(new CodeSnippet_Constructor({ "LoadParsingTable();" }, { "const std::vector<PC::Token*>& TokenStream" }, { {"Parser", "TokenStream" } }));

		// Add Parsing Rules
		ClassSnippet->CreateNewGroup("public");
		for (const std::string& NonTerminal : InAlphabet->GetNonTerminalNames())
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

			std::vector<RuleDefinition*> NonTerminalRules = ParsConfig->GetAllProductionsForNonTerminal(NonTerminal);
			if (NonTerminalRules.size() == 1)
			{
				for (RuleElement* Element : NonTerminalRules[0]->m_RuleElements)
				{
					if (Element->IsNonTerminal())
					{
						std::string ElementFunctionName = Element->m_Content;
						ElementFunctionName[0] = toupper(ElementFunctionName[0]);
						std::string ElementRuleName = "Rule_" + Element->m_Content;
						BodyLines.push_back("CALL_CHILD(" + ElementFunctionName + ", " + ElementRuleName + ");");
					}
					else
					{
						std::string ElementTokenName = StringUtils::ToUpperCase(Element->m_Content);
						BodyLines.push_back("TRY_MATCH(ETokenType::" + ElementTokenName + ");");
					}
				}
			}
			else
			{
				CodeSnippet_Switch* SwitchSnippet = new CodeSnippet_Switch("PredictProduction()");
				for (RuleDefinition* Rule : NonTerminalRules)
				{
					std::vector<std::string> CaseLines;
					for (RuleElement* Element : Rule->m_RuleElements)
					{
						if (Element->IsEpsilon())
						{
							CaseLines.push_back("// EPSILON");
						}
						else if (Element->IsNonTerminal())
						{
							std::string ElementFunctionName = Element->m_Content;
							ElementFunctionName[0] = toupper(ElementFunctionName[0]);
							std::string ElementRuleName = "Rule_" + Element->m_Content;
							CaseLines.push_back("CALL_CHILD(" + ElementFunctionName + ", " + ElementRuleName + ");");
						}
						else
						{
							std::string ElementTokenName = StringUtils::ToUpperCase(Element->m_Content);
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

		if (m_NamespaceName.empty())
		{
			ParserFile->AddSnippet(RootSnippets);
		}
		else
		{
			CodeSnippet_Namespace* NamespaceSnippet = new CodeSnippet_Namespace(m_NamespaceName);
			ParserFile->AddSnippet(NamespaceSnippet);
			NamespaceSnippet->AttachSnippet(RootSnippets);
		}

		return true;
	}

	bool ParserSerializer::WriteVisitorCode(Alphabet* InAlphabet) const
	{
		// Create File
		std::string FileName = ExtendFileName("VisitorBase");
		FileTemplate* VisitorFile = m_Generator->CreateVirtualFile(FileName, m_CodePath);
		std::vector<CodeSnippet_Base*> RootSnippets;

		// Add Includes
		VisitorFile->AddSnippet(new CodeSnippet_Include(ExtendFileName("Rules") + ".h"));
		VisitorFile->AddSnippet(new CodeSnippet_Include("ParserCore.h", false));

		// Add Visitor BaseClass
		CodeSnippet_Class* ClassSnippet = new CodeSnippet_Class(FileName, "PC::Visitor<T>");
		RootSnippets.push_back(ClassSnippet);
		ClassSnippet->AddTemplating({ "T" });

		// Add virtual Visit Functions
		ClassSnippet->CreateNewGroup("public");
		for (const std::string& NonTerminal : InAlphabet->GetNonTerminalNames())
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

		for (const std::string& NonTerminal : InAlphabet->GetNonTerminalNames())
		{
			std::string FunctionName = "VisitRule_" + NonTerminal;
			std::string RuleName = "Rule_" + NonTerminal;
			ClassSnippet->AttachSnippet(new CodeSnippet_Function("Visit<" + RuleName + ">", { "return " + FunctionName + "(Context);" }, { RuleName + "* Context" }, "T", { TEMPLATE, SINGLELINE, HEADERDEFINITION }));
		}

		if (m_NamespaceName.empty())
		{
			VisitorFile->AddSnippet(RootSnippets);
		}
		else
		{
			CodeSnippet_Namespace* NamespaceSnippet = new CodeSnippet_Namespace(m_NamespaceName, false);
			VisitorFile->AddSnippet(NamespaceSnippet);
			NamespaceSnippet->AttachSnippet(RootSnippets);
		}

		return true;
	}

	void ParserSerializer::Finish() const
	{
		m_Generator->GenerateFiles();
	}

	bool ParserSerializer::SerializeParsingTable(PCT::ParsingTable* InTable, std::string& OutString) const
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

	bool ParserSerializer::SerializeAutomaton(PCA::DFA* InDFA, std::string& OutString) const
	{
		std::stringstream StateStream;
		std::stringstream TransitionStream;

		std::map<PCA::State*, int> IndexMap;
		int StateIndex = 0;
		for (const std::pair<std::string, PCA::State*>& Element : InDFA->GetStateMap())
		{
			// Write State Data
			PCA::State* ActiveState = Element.second;
			int ActiveIndex = IndexMap.find(ActiveState) != IndexMap.end() ? IndexMap[ActiveState] : IndexMap[ActiveState] = StateIndex++;
			StateStream << " " << ActiveIndex << " " << ActiveState->GetStatePriority();

			// Write Transition Data
			for (PCA::Transition* Trans : ActiveState->GetTransitions())
			{
				PCA::State* OtherState = Trans->GetTargetState();
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

	void ParserSerializer::WriteTokenList(Alphabet* InAlphabet, std::stringstream& TokenStream) const
	{
		for (const std::pair<int, std::string>& Pair : InAlphabet->GetTokenNameMap())
		{
			TokenStream << Pair.first << " " << Pair.second << std::endl;
		}
	}

	void ParserSerializer::WriteNonTerminalList(Alphabet* InAlphabet, std::stringstream& NonTerminalStream) const
	{
		for (const std::pair<int, std::string>& Pair : InAlphabet->GetRuleNameMap())
		{
			NonTerminalStream << Pair.first << " " << Pair.second << std::endl;
		}
	}

	std::string ParserSerializer::ExtendFileName(const std::string& RawFileName) const
	{
		return m_ParserName + RawFileName;
	}

}