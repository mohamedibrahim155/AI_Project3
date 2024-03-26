#include "CohesionBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
void CohesionBehaviour::Start()
{
}

void CohesionBehaviour::UpdateState(float deltaTime)
{
}

void CohesionBehaviour::Render()
{
}

glm::vec2 CohesionBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec2(0);

	glm::vec2 cohesionMove = glm::vec2(0);

	for (Transform* transform : context)
	{
		cohesionMove += glm::vec2(transform->position);
	}

	cohesionMove /= context.size();

	cohesionMove += glm::vec2(agent->transform.position) /**2.0f*/;

	return cohesionMove;
}
