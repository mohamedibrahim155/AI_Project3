#pragma once
#include "BaseBehaviour.h"
class AvoidanceBehaviour : public BaseBehaviour
{
public:
	// Inherited via BaseBehaviour
	void Start() override;
	void UpdateState(float deltaTime) override;
	void Render() override;
	glm::vec3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager) override;
};

