#pragma once
#include "BaseBehaviour.h"
class SteeredCohesionBehaviour : public BaseBehaviour
{
public:

	glm::vec3 currentVelocity;
	float agentSmoothTime = 0.2f;

		// Inherited via BaseBehaviour
	void Start() override;
	void UpdateState(float deltaTime) override;
	void Render() override;
	glm::vec3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager) override;
};

