#include "SteeredCohesionBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
#include "../../../Math.h"
#include "../../../Time.h"
using namespace MathUtils;

void SteeredCohesionBehaviour::Start()
{
}

void SteeredCohesionBehaviour::UpdateState(float deltaTime)
{
}

void SteeredCohesionBehaviour::Render()
{
}

glm::vec2 SteeredCohesionBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
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

	
	cohesionMove = Math::SmoothDampVec2(
		glm::vec2(agent->transform.GetUp()),
		cohesionMove, 
		currentVelocity, 
		agentSmoothTime,1, Time::GetInstance().deltaTime);

	return cohesionMove;
}
