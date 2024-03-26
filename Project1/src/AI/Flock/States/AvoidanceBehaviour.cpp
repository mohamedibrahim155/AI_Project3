#include "AvoidanceBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
#include "../../../Math.h"

using namespace MathUtils;

void AvoidanceBehaviour::Start()
{
}

void AvoidanceBehaviour::UpdateState(float deltaTime)
{
}

void AvoidanceBehaviour::Render()
{
}

glm::vec3 AvoidanceBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec3(0);

	glm::vec3 avoidanceMove = glm::vec3(0);
	int avoidCount = 0;


	for (Transform* transform : context)
	{
		if (Math::squareMagnitudeVec3(transform->position - agent->transform.position) < flockManager->GetSquareAvoidanceRadius())
		{
			avoidCount++;

			avoidanceMove += glm::vec3(agent->transform.position - transform->position);
		}
		
	}

	if (avoidCount>0)
	{
		avoidanceMove /= avoidCount;
	}
	return avoidanceMove;
}
