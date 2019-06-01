#pragma once

#include "ParseTree.h"
#include "../../Lexer/Token.h"

namespace ParserCore {

	class TokenNode : public ParseTree
	{
	protected:
		Token* m_Token;
		ParseTree* m_Parent;

	public:
		TokenNode(Token* InToken);
		~TokenNode();

		// Inherited via ParseTree
		virtual ParseTree* GetParent() const override;
		virtual ParseTree* GetChild(int Index) const override;
		virtual int GetChildCount() const override;
		virtual void SetParent(ParseTree* InParent) override;

	public:
		const std::string& GetText() const { return m_Token->GetTokenData(); }
		Token* GetSymbol() const { return m_Token; }

		int GetTokenType() const;
		bool IsTokenType(int InTokenType) const;
	};

}