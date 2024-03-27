#pragma once
#include "BaseBehaviour.h"
class StayInRadiusBehaviour : public BaseBehaviour
{
	public:

		glm::vec3 centre;
		float radius = 15.0f;

		// Inherited via BaseBehaviour
		void Start() override;

		void UpdateState(float deltaTime) override;

		void Render() override;

		glm::vec3 CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager) override;

		void SetRadius(float radius);
};

