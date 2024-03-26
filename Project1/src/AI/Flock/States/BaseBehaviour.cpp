#include "BaseBehaviour.h"
#include"../FlockAgent.h"
BaseBehaviour::BaseBehaviour(FlockAgent* agent)
{
	this->agent = agent;
}

void BaseBehaviour::OnBehaviourChange(Behaviour state)
{
	agentState = state;
}
