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

glm::vec2 AlignmentBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec2(agent->transform.GetUp());

	glm::vec2 alignMove = glm::vec2(0);

	for (Transform* transform : context)
	{
		alignMove += glm::vec2(transform->GetUp());
	}

	alignMove /= context.size();


	return alignMove;
}
