#pragma once

#include "../CodeSnippet.h"
#include <set>

namespace ParserCore {

	enum EFunctionModifier {
		VIRTUAL,
		OVERRIDE,
		INLINE,
		CONSTANT,
		STATIC,
		HEADERDEFINITION,
		SINGLELINE,
		TEMPLATE
	};

	class CodeSnippet_Function : public CodeSnippet_Base
	{
	protected:
		std::string m_FunctionName;
		std::vector<std::string> m_FunctionBody;
		std::vector<std::string> m_FunctionParameters;
		//CodeSnippet_Parameter* m_ReturnParameter;
		std::string m_ReturnType;

		std::vector<std::string> m_TypeNames;

		std::set<EFunctionModifier> m_ModifierList;

		/*bool m_bHeaderDefinition;
		bool m_bStatic;
		bool m_bConstant;
		bool m_bInline;
		bool m_bVirtual;
		bool m_bOverride;
		bool m_bSingleLine;*/

	public:
		CodeSnippet_Function(const std::string& InFunctionName, const std::vector<std::string>& InFunctionBody, const std::string& InReturnType = "void", const std::set<EFunctionModifier> InModifier = {})
			: CodeSnippet_Function(InFunctionName, InFunctionBody, {}, InReturnType, InModifier)
		{ }

		CodeSnippet_Function(const std::string& InFunctionName, const std::vector<std::string>& InFunctionBody, const std::vector<std::string>& InFunctionParameters, const std::string& InReturnType = "void", const std::set<EFunctionModifier> InModifier = {})
			: CodeSnippet_Base(1), m_FunctionName(InFunctionName), m_FunctionBody(InFunctionBody), m_FunctionParameters(InFunctionParameters), m_ReturnType(InReturnType), m_ModifierList(InModifier)
		{ }

		void AddTemplating(const std::vector<std::string>& InTypeNames);

	public:
		// Inherited via CodeSnippet_Base
		virtual void Write() const override;

	protected:
		inline bool IsStatic() const { return m_ModifierList.find(EFunctionModifier::STATIC) != m_ModifierList.end(); }
		inline bool IsConstant() const { return m_ModifierList.find(EFunctionModifier::CONSTANT) != m_ModifierList.end(); }
		inline bool IsInline() const { return m_ModifierList.find(EFunctionModifier::INLINE) != m_ModifierList.end(); }
		inline bool IsVirtual() const { return m_ModifierList.find(EFunctionModifier::VIRTUAL) != m_ModifierList.end(); }
		inline bool IsOverride() const { return m_ModifierList.find(EFunctionModifier::OVERRIDE) != m_ModifierList.end(); }
		inline bool IsHeaderDefinition() const { return m_ModifierList.find(EFunctionModifier::HEADERDEFINITION) != m_ModifierList.end(); }
		inline bool IsSingleLine() const { return m_ModifierList.find(EFunctionModifier::SINGLELINE) != m_ModifierList.end(); }
		inline bool IsTemplate() const { return m_ModifierList.find(EFunctionModifier::TEMPLATE) != m_ModifierList.end(); }

		const std::string GetClassName() const;
		std::string CreateParameterString() const;
	};

}