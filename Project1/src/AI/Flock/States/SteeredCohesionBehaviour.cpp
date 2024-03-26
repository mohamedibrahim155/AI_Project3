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

glm::vec3 SteeredCohesionBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
	if (context.size() == 0)
		return glm::vec3(0);

	glm::vec3 cohesionMove = glm::vec3(0);

	for (Transform* transform : context)
	{
		cohesionMove += glm::vec3(transform->position);
	}

	cohesionMove /= context.size();

	cohesionMove -= glm::vec3(agent->transform.position) /**2.0f*/;

	
	cohesionMove = Math::SmoothDampVec3(
		glm::vec3(agent->transform.GetUp()),
		cohesionMove, 
		currentVelocity, 
		agentSmoothTime,1, Time::GetInstance().deltaTime);

	return cohesionMove;
}
