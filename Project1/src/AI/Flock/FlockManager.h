#pragma once
#include "FlockAgent.h"
#include "../../EntityManager/EntityManager.h"
#include "States/BaseBehaviour.h"
#include <unordered_map>
class FlockManager : public Entity
{
public:
	FlockManager();
	~FlockManager();

	//static FlockManager& GetInstance();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	void Render() override;
	void DrawProperties()override;
	void SceneDraw()override;

	void AddAgent(FlockAgent* agent);
	void RemoveAgent(FlockAgent* agent);

	void AddBehaviourState(Behaviour state, BaseBehaviour* currentBehaviour);
	void RomoveBehaviourState(Behaviour state);

	BaseBehaviour* GetBehaviourState(Behaviour state);

	void OnBehaviourChange(Behaviour state);

	float GetSquareAvoidanceRadius();
	std::vector<Transform*> GetNearByObjects(FlockAgent* agent);
	BaseBehaviour* GetCurrentBehaviour();



private:
	float agentDensity = 0.5f;
	float driveFactor = 5;
	float maxSpeed = 2;
	float neighbourRadius = 1;
	float avoidanceRadiusMultiplier = 1.5f;
	float squaredMaxSpeed;
	float squareAvoidanceRadius;
	float squareNeighbourRadius;

	int flockAgentCount = 20;
	bool showDebug = true;
	bool allAgentSpawned = false;
	std::vector<FlockAgent*> listOfFlockAgents;
	std::unordered_map<Behaviour, BaseBehaviour*> listOfBehaviours;

	BaseBehaviour* currentBehaviour;



};

