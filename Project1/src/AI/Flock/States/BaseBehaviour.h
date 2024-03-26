#pragma once
#include "State.h"
#include "glm/glm.hpp"
#include <vector>
class FlockAgent;
class FlockManager;
class Transform;

class BaseBehaviour
{
public:

	BaseBehaviour();

	virtual void Start() = 0;
	virtual void UpdateState(float deltaTime) = 0;
	virtual void Render() = 0;

	virtual void OnBehaviourChange(Behaviour state);

	virtual glm::vec3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager) = 0;

	Behaviour agentState = Behaviour::COHESION;
private:
};

