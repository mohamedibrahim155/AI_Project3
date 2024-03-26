#pragma once
#include "../model.h"
#include <unordered_map>
#include "IdleState.h"
#include "MoveState.h"

struct EnemyInfo
{
	float Speed = 2;
	float WaitTime =0.2f;

	float xRange = 30;
	float zRange = 17;
};

class Enemy : public Model
{
public:
	Enemy(EnemyInfo& enemy);

    void DrawProperties() override;
    void SceneDraw()override;

    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnDestroy() override;

	BaseEnemyState* GetCurrentState();
	BaseEnemyState* GetState(eStates state);

	void IntialState(eStates state);
	void OnStateChange(eStates state);
	void AddState(eStates state, BaseEnemyState* enemyState);
	void RemoveState(eStates state);

	EnemyInfo enemyInfo;

	void SetColor(const glm::vec4& color);

private:
	BaseEnemyState* currentState;

	std::unordered_map<eStates, BaseEnemyState*> listOfEnemyStates;

};

