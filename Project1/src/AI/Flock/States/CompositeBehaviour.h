#pragma once
#include "BaseBehaviour.h"
class CompositeBehaviour : public BaseBehaviour
{
public:

	std::vector<BaseBehaviour*> behaviours;
	std::vector<float> weights;

	// Inherited via BaseBehaviour
	void Start() override;
	void UpdateState(float deltaTime) override;
	void Render() override;
	glm::vec2 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager) override;
};

