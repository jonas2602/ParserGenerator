#include "Node.h"

namespace ParserGenerator {

	void Node_CONST::ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		OutStart = OutMachine->CreateNewState(Name);
		OutEnd = OutMachine->CreateNewState(Name, FinalStatePriority);

		OutMachine->CreateNewTransition(OutStart, OutEnd, m_CharSet);
	}


	void Node_OR::ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		OutStart = OutMachine->CreateNewState(Name);
		OutEnd = OutMachine->CreateNewState(Name, FinalStatePriority);

		for (Node_BASE* Node : m_Content)
		{
			PCA::State* NodeStart;
			PCA::State* NodeEnd;
			Node->ExtendMachine(OutMachine, NodeStart, NodeEnd, Name, -1);
			OutMachine->CreateNewTransition(OutStart, NodeStart, { PC::EPSILON });
			OutMachine->CreateNewTransition(NodeEnd, OutEnd, { PC::EPSILON });
		}
	}



	void Node_AND::ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		for (int i = 0; i < m_Content.size(); i++)
		{
			PCA::State* NodeStart;
			PCA::State* NodeEnd;
			m_Content[i]->ExtendMachine(OutMachine, NodeStart, NodeEnd, Name, -1);

			// First Element -> Set Global Start
			if (i == 0) OutStart = NodeStart;

			// Has Previous Element? -> Connect to Last
			if (i > 0) OutMachine->CreateNewTransition(OutEnd, NodeStart, { PC::EPSILON });

			// Update Global End
			OutEnd = NodeEnd;
		}
	}





	void Node_STAR::ExtendMachine(NFA* OutMachine, PCA::State*& OutStart, PCA::State*& OutEnd, const std::string& Name, int FinalStatePriority)
	{
		PCA::State* ContentStart;
		PCA::State* ContentEnd;
		m_Content->ExtendMachine(OutMachine, ContentStart, ContentEnd, Name, -1);

		OutStart = OutMachine->CreateNewState(Name);
		OutEnd = OutMachine->CreateNewState(Name, FinalStatePriority);

		OutMachine->CreateNewTransition(ContentEnd, ContentStart, { PC::EPSILON });
		OutMachine->CreateNewTransition(OutStart, ContentStart, { PC::EPSILON });
		OutMachine->CreateNewTransition(ContentEnd, OutEnd, { PC::EPSILON });
		OutMachine->CreateNewTransition(OutStart, OutEnd, { PC::EPSILON });
	}

}