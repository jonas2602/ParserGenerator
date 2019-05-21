#pragma once

#include <vector>

//#include "../Core.h"
//#include "../Lexer/Token.h"
//#include "ParserConfig.h"


namespace ParserGenerator {
	/*class ParseTree;


	class ParseNode
	{
	protected:
		std::vector<ParseNode*> m_Children;

	public:
		ParseNode()
		{ }

		const std::vector<ParseNode*>& GetChildren() const { return m_Children; }

		friend ParseTree;
	};

	class ParseNode_Token : public ParseNode
	{
	protected:
		Token* m_Token;

	public:
		ParseNode_Token(Token* InToken)
			:m_Token(InToken)
		{ }

		const std::string& GetText() const { return m_Token->GetTokenData(); }
	};

	class ParseNode_Production : public ParseNode
	{
	protected:
		ParserConfigElement* m_Production;

	public:

		ParseNode_Production(ParserConfigElement* InProduction)
			:m_Production(InProduction)
		{ }
	};*/


	class ParseTree
	{
	public:
		virtual ParseTree* GetParent() const = 0;
		virtual ParseTree* GetChild(int Index) const = 0;
		virtual int GetChildCount() const = 0;

		virtual void SetParent(ParseTree* InParent) = 0;

		/*protected:
			ParseNode* m_RootNode;

		public:
			ParseTree();
			~ParseTree();

			ParseNode_Token* InsertTokenNode(ParseNode* Parent, Token* InToken);
			ParseNode_Production* InsertProductionNode(ParseNode* Parent, ParserConfigElement* InProduction);

			ParseNode_Production* GetRootNode() const { return (ParseNode_Production*)m_RootNode; }

		protected:
			void AddNodeToTree(ParseNode* Parent, ParseNode* Child);*/
	};

}