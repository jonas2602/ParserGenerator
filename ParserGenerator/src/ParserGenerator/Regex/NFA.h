#pragma once
#include <ParserCore.h>

namespace ParserGenerator {

	class NFA : public PCA::Automaton
	{
	protected:
		std::set<PCA::State*> m_StartStates;

	public:
		std::set<PCA::State*> GetStartStates() const { return m_StartStates; }
		void AddStartState(PCA::State* StartState);

	protected:
		std::set<PCA::State*> BuildEpsilonHull(const std::set<PCA::State*>& InStates) const;
		std::set<PCA::State*> BuildEpsilonHull_Min(const std::set<PCA::State*>& InStates) const;

		// TODO: Optimize with ranges, ...
		std::map<std::set<PCA::State*>, std::set<char>> BuildTransitionMap(const std::set<PCA::State*>& StateList) const;

		std::string CreateCombinedName(const std::set<PCA::State*>& States) const;

		// -1 no final state, >= 0 index of prioritised regex with final state in this state
		int FindPrioritisedFinalState(const std::set<PCA::State*>& States) const;
	public:
		void CreateDFA(PCA::DFA*& OutDFA) const;
	};
}