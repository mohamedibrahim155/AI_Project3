#include "CompositeBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
#include "../../../Math.h"

using namespace MathUtils;

void CompositeBehaviour::Start()
{
}

void CompositeBehaviour::UpdateState(float deltaTime)
{
}

void CompositeBehaviour::Render()
{
}

glm::vec3 CompositeBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (weights.size()!= behaviours.size())
	{
		std::cout << "Error with Behaviour Count" << std::endl;
		return glm::vec3(0);
	}

	glm::vec3 move = glm::vec3(0);

	for (int i = 0; i < behaviours.size(); i++)
	{
		glm::vec3 partialMove = behaviours[i]->CalculateMove(agent, context, flockManager) * weights[i];

		if (partialMove != glm::vec3(0))
		{
			if (Math::squareMagnitude(partialMove) > weights[i] * weights[i])
			{
				partialMove = glm::normalize(partialMove);
				partialMove *= weights[i];
			}

			move += partialMove;
		}

	}
	return move;
}
