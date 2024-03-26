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

glm::vec3 CohesionBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec3(0);

	glm::vec3 cohesionMove = glm::vec3(0);

	for (Transform* transform : context)
	{
		cohesionMove += glm::vec3(transform->position);
	}

	cohesionMove /= context.size();

	cohesionMove += agent->transform.position /**2.0f*/;

	return cohesionMove;
}
