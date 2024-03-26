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

glm::vec2 AvoidanceBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec2(0);

	glm::vec2 avoidanceMove = glm::vec2(0);
	int avoidCount = 0;


	for (Transform* transform : context)
	{
		if (Math::squareMagnitude(transform->position - agent->transform.position) < flockManager->GetSquareAvoidanceRadius())
		{
			avoidCount++;

			avoidanceMove += glm::vec2(agent->transform.position - transform->position);
		}
		
	}

	if (avoidCount>0)
	{
		avoidanceMove /= avoidCount;
	}
	return avoidanceMove;
}
