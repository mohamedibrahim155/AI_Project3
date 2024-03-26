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

glm::vec2 CompositeBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (weights.size()!= behaviours.size())
	{
		std::cout << "Error with Behaviour Count" << std::endl;
		return glm::vec2(0);
	}

	glm::vec2 move = glm::vec2(0);

	for (int i = 0; i < behaviours.size(); i++)
	{
		glm::vec2 partialMove = behaviours[i]->CalculateMove(agent, context, flockManager) * weights[i];

		if (partialMove != glm::vec2(0))
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
