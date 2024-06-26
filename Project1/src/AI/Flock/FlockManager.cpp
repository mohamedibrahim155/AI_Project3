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
#include "States/StayInRadiusBehaviour.h"
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
    AddBehaviourState(Behaviour::STAYINSIDE_RANGE, new StayInRadiusBehaviour());

    currentBehaviour = GetBehaviourState(Behaviour::COMPOSITE);

    ////((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::COHESION));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::STEERED));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::ALIGNMENT));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::AVOIDANCE));
    ((CompositeBehaviour*)currentBehaviour)->behaviours.push_back(GetBehaviourState(Behaviour::STAYINSIDE_RANGE));


    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(4);
    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(1);
    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(2);
    ((CompositeBehaviour*)currentBehaviour)->weights.push_back(3);

    //currentBehaviour = GetBehaviourState(Behaviour::ALIGNMENT);

    IntializeFlocks(0);

}


FlockManager::~FlockManager()
{
    Destroy();
}


void FlockManager::Start()
{
    squaredMaxSpeed = maxSpeed * maxSpeed;
    squareNeighbourRadius = neighbourRadius * neighbourRadius;
    squareAvoidanceRadius = squareNeighbourRadius * avoidanceRadiusMultiplier * avoidanceRadiusMultiplier;

    allAgentSpawned = false;

    IntializeFlocks(listOfFlockAgents.size());
  
}

void FlockManager::Update(float deltaTime)
{
    if (!allAgentSpawned)
    {
        return;
    }
    squareAvoidanceRadius = squareNeighbourRadius * avoidanceRadiusMultiplier * avoidanceRadiusMultiplier;

    for (FlockAgent* agent : listOfFlockAgents)
    {
        std::vector<Transform*> context = GetNearByObjects(agent);
        
        glm::vec4 white = glm::vec4(1);
        glm::vec4 red = glm::vec4(1, 0, 0, 1);
        glm::vec4 lerpValue = Math::LerpVec4(white, red, context.size()/2.0f);

        agent->SetAgentColor(lerpValue);

        glm::vec3 move = GetCurrentBehaviour()->CalculateMove(agent, context, this);

        move *= driveFactor;

        if (glm::length(move) > squaredMaxSpeed )
        {
            move = glm::normalize(move) * maxSpeed;
        }

        agent->Move(move);

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

void FlockManager::DrawProperties()
{
    Entity::DrawProperties();

    DrawFlockManagerProperties();
}

void FlockManager::SceneDraw()
{
    Entity::SceneDraw();
}

void FlockManager::IntializeFlocks(int alreadySpawnedCount)
{
    int agentRequiredCount = flockAgentCount - alreadySpawnedCount;

    for (int i = 0; i < agentRequiredCount; i++)
    {
        glm::vec2 position = Math::randomInsideUnitCircle() * ((float)flockAgentCount +(float)agentRequiredCount)  * agentDensity;
        FlockAgent* newAgent = new FlockAgent(glm::vec3(position, 0));

        glm::vec3 forward = glm::vec3(0, 0, 1);
        float randomValue = Math::GetRandomFloatNumber(0.0f, 360.0f);

        newAgent->transform.SetRotation(forward * randomValue);

        newAgent->name = "Agent " + std::to_string(listOfFlockAgents.size() + 1);

        AddAgent(newAgent);

    }

    allAgentSpawned = true;
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

void FlockManager::DrawFlockManagerProperties()
{
    ImGui::NewLine();

    if (!ImGui::TreeNodeEx("FlockManager", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    ImGui::Text("Show debug");
    ImGui::SameLine();
    if (!ImGui::Checkbox("###ShowDebug", &showDebug))
    {
        ImGui::Text("Flocks Count");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);
        ImGui::DragInt("##FlockCount", &flockAgentCount, 0.1f, 0, 50);

        ImGui::Text("Avoidaance Radius");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);
        ImGui::DragFloat("##AvoidanceMultiplier", &avoidanceRadiusMultiplier, 0.1f, 0, 0, "%0.2f");

        ImGui::Text("Neighbour radius");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);

        ImGui::DragFloat("##Neighbourradius", &neighbourRadius, 0.1f, 0.0f, 3.0f, "%0.2f");

        ImGui::Text("Max Speed");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);
        ImGui::DragFloat("##maxSpeed", &maxSpeed, 0.1f, 0, 0, "%0.2f");

        ImGui::Text("Area Radius");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);
        if (!ImGui::DragFloat("##AreaRadius", &areaRadius, 0.1f, 0, 25, "%0.2f"))
        {
            ((StayInRadiusBehaviour*)GetBehaviourState(Behaviour::STAYINSIDE_RANGE))->SetRadius(areaRadius);
        }

    }


    ImGui::TreePop();
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

        //if (distance > 0);
        {
            if (distance < neighbourRadius * neighbourRadius)
            {
                context.push_back(&otheragent->transform);
            }
        }

    }

    return context;
}
