#pragma once
#include "State.h"
class FlockAgent;


class BaseBehaviour
{
public:

	BaseBehaviour(FlockAgent* agent);

	virtual void Start() = 0;
	virtual void UpdateState(float deltaTime) = 0;
	virtual void Render() = 0;

	virtual void OnBehaviourChange(Behaviour state);

	Behaviour agentState = Behaviour::IDLE;
private:
	FlockAgent* agent =  nullptr;
};

