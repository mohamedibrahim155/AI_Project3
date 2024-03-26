#include "BaseBehaviour.h"
#include"../FlockAgent.h"

BaseBehaviour::BaseBehaviour()
{
}

void BaseBehaviour::OnBehaviourChange(Behaviour state)
{
	agentState = state;
}
