#pragma once
#include "FlockAgent.h"
#include "../../EntityManager/EntityManager.h"
#include "States/BaseBehaviour.h"

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

	void AddAgent(FlockAgent* agent);
	void RemoveAgent(FlockAgent* agent);

	void OnBehaviourChange(Behaviour state);

	BaseBehaviour* GetCurrentBehaviour();
	float GetSquareAvoidanceRadius();

private:
	float agentDensity = 0.8f;
	float driveFactor = 10.0f;
	float maxSpeed = 5.0f;
	float neighbourRadius = 1.5f;
	float avoidanceRadiusMultiplier = 0.5f;
	float squaredMaxSpeed;
	float squareAvoidanceRadius;
	float squareNeighbourRadius;

	int flockAgentCount = 10;

	std::vector<FlockAgent*> listOfFlockAgents;
	BaseBehaviour* behaviour;


};

