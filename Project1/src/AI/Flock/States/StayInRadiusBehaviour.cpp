#include "StayInRadiusBehaviour.h"
#include "../../Flock/FlockAgent.h"
#include "../FlockManager.h"
#include "../../../Math.h"
#include "../../../Time.h"
using namespace MathUtils;
void StayInRadiusBehaviour::Start()
{
}

void StayInRadiusBehaviour::UpdateState(float deltaTime)
{
}

void StayInRadiusBehaviour::Render()
{
}

glm::vec3 StayInRadiusBehaviour::CalculateMove(FlockAgent* agent, std::vector<Transform*> context, FlockManager* flockManager)
{
    glm::vec3 centreOffset = centre - agent->transform.position;

    float t = glm::length(centreOffset) / radius;

    if (t <0.9f)
    {
        return glm::vec3(0);
    }



    return centreOffset * t * t;
}
