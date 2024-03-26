#pragma once
#include <unordered_map>
#include "BaseEnemyState.h"

class EnemyStateMachine
{
public:
	EnemyStateMachine();


	BaseEnemyState* currentState;
	BaseEnemyState* GetCurrentState();
	BaseEnemyState* GetState(eStates state);

	void IntialState(eStates state);
	void OnStateChange(eStates state);
	void AddState(eStates state, BaseEnemyState* enemyState);
	void RemoveState(eStates state);
	//void Update(float deltaTime);

	std::unordered_map<eStates, BaseEnemyState*> listOfEnemyStates;
};

