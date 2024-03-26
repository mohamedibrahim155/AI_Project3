#include "AlignmentBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
void AlignmentBehaviour::Start()
{
}

void AlignmentBehaviour::UpdateState(float deltaTime)
{
}

void AlignmentBehaviour::Render()
{
}

glm::vec3 AlignmentBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec3(agent->transform.GetUp());

	glm::vec3 alignMove = glm::vec3(0);

	for (Transform* transform : context)
	{
		alignMove += glm::vec3(transform->GetUp());
	}

	alignMove /= context.size();


	return alignMove;
}
