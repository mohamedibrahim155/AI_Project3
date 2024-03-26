#include "FlockManager.h"
#include "../../Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "States/CohesionBehaviour.h"
#include "States/AlignmentBehaviour.h"
#include "States/AvoidanceBehaviour.h"
#include "States/CompositeBehaviour.h"
#include "States/SteeredCohesionBehaviour.h"
#include "../../GraphicsRender.h"
using namespace MathUtils;

FlockManager::FlockManager()
{
    name = "Flock Manager";
    InitializeEntity(this);

    AddBehaviourState(Behaviour::COHESION, new CohesionBehaviour());
    AddBehaviourState(Behaviour::AVOIDANCE, new AvoidanceBehaviour());
    AddBehaviourState(Behaviour::ALIGNMENT, new AlignmentBehaviour());
    AddBehaviourState(Behaviour::COMPOSITE, new CompositeBehaviour());
    AddBehaviourState(Behaviour::STEERED, new SteeredCohesionBehaviour());

    currentBehaviour = GetBehaviourState(Behaviour::COMPOSITE);

    //((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::COHESION));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::STEERED));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::ALIGNMENT));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::AVOIDANCE));


    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(4);
    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(1);
    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(2);


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

        FlockAgent* newAgent = new FlockAgent(glm::vec3(position,0));

        glm::vec3 forward = glm::vec3(0, 0, 1);
        float randomValue = Math::GetRandomFloatNumber(0.0f, 360.0f);

        newAgent->transform.SetRotation(forward * randomValue);

        newAgent->name = "Agent " + std::to_string(i);
        
        AddAgent(newAgent);

    }

}

void FlockManager::Update(float deltaTime)
{
    for (FlockAgent* agent : listOfFlockAgents)
    {
        std::vector<Transform*> context = GetNearByObjects(agent);
        
        glm::vec4 white = glm::vec4(1);
        glm::vec4 red = glm::vec4(1, 0, 0, 1);
        glm::vec4 lerpValue = Math::LerpVec4(white, red, context.size()/3.0f);

        agent->SetAgentColor(lerpValue);

        glm::vec2 move = GetCurrentBehaviour()->CalculateMove(agent, context, this);

        move *= driveFactor;

        if (Math::squareMagnitude(move) > squaredMaxSpeed )
        {
            move = glm::normalize(move) * maxSpeed;
        }
        agent->Move(glm::vec3(move, transform.position.z));

    }
}

void FlockManager::OnDestroy()
{
}

void FlockManager::Render()
{
    if (!showDebug) return;

    for (FlockAgent* agent : listOfFlockAgents)
    {
        GraphicsRender::GetInstance().DrawSphere(agent->transform.position,
            neighbourRadius, 
            glm::vec4(0, 0.25f, 1, 1)
            , true);
    }
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

void FlockManager::AddBehaviourState(Behaviour state, BaseBehaviour* currentBehaviour)
{
    listOfBehaviours[state] = currentBehaviour;
}

void FlockManager::RomoveBehaviourState(Behaviour state)
{
    std::unordered_map<Behaviour, BaseBehaviour*>::iterator it = listOfBehaviours.find(state);
    if (it!= listOfBehaviours.end())
    {
        listOfBehaviours.erase(it);
    }
}

BaseBehaviour* FlockManager::GetBehaviourState(Behaviour state)
{
    return listOfBehaviours[state];
}

void FlockManager::OnBehaviourChange(Behaviour state)
{
    currentBehaviour = GetBehaviourState(state);
}

BaseBehaviour* FlockManager::GetCurrentBehaviour()
{
    return currentBehaviour;
}

float FlockManager::GetSquareAvoidanceRadius()
{
    return squareAvoidanceRadius;
}

std::vector<Transform*> FlockManager::GetNearByObjects(FlockAgent* agent)
{
    std::vector<Transform*> context;

    for (FlockAgent* otheragent :  listOfFlockAgents)
    {
        if (agent == otheragent) continue;

        float distance = glm::length(agent->transform.position
            - otheragent->transform.position);

        //if (glm::length(displacement) >= 0);
        {
            if (distance <= neighbourRadius)
            {
                context.push_back(&otheragent->transform);
            }
        }

    }

    return context;
}
