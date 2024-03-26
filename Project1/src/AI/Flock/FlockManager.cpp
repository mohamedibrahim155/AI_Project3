#include "FlockManager.h"
#include "../../Math.h"
using namespace MathUtils;

FlockManager::FlockManager()
{
    name = "Flock Manager";
    InitializeEntity(this);
}

FlockManager::~FlockManager()
{
    Destroy();
}

//FlockManager& FlockManager::GetInstance()
//{
//    static FlockManager instance;
//
//    return instance;
//}

void FlockManager::Start()
{
    squaredMaxSpeed = maxSpeed * maxSpeed;
    squareNeighbourRadius = neighbourRadius * neighbourRadius;
    squareAvoidanceRadius = squareNeighbourRadius * avoidanceRadiusMultiplier * avoidanceRadiusMultiplier;

    for (int i = 0; i < flockAgentCount; i++)
    {
        glm::vec2 position = Math::randomInsideUnitCircle() * (float)flockAgentCount * agentDensity;

        FlockAgent* newAgent = new FlockAgent(glm::vec3(position,1));

        glm::vec3 forward = glm::vec3(0, 0, 1);
        float randomValue = Math::GetRandomFloatNumber(0.0f, 360.0f);

        newAgent->transform.SetRotation(forward * randomValue);

        newAgent->name = "Agent " + std::to_string(i);
        
        AddAgent(newAgent);

    }

}

void FlockManager::Update(float deltaTime)
{
}

void FlockManager::OnDestroy()
{
}

void FlockManager::Render()
{
}

void FlockManager::AddAgent(FlockAgent* agent)
{
    listOfFlockAgents.push_back(agent);
}

void FlockManager::RemoveAgent(FlockAgent* agent)
{
    std::vector<FlockAgent*>::iterator it = std::find(listOfFlockAgents.begin(),
        listOfFlockAgents.end(), agent);

    if (it != listOfFlockAgents.end())
    {
        listOfFlockAgents.erase(it);
    }
}

void FlockManager::OnBehaviourChange(Behaviour state)
{
}

BaseBehaviour* FlockManager::GetCurrentBehaviour()
{
    return behaviour;
}

float FlockManager::GetSquareAvoidanceRadius()
{
    return squareAvoidanceRadius;
}
