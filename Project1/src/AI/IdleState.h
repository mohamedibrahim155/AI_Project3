#pragma once
#include "BaseEnemyState.h"

class Enemy;
class IdleState : public BaseEnemyState
{
public:
	IdleState(Enemy* enemy);

	// Inherited via BaseState
	void StartState() override;
	void ExitState() override;
	void UpdateState(float deltatime) override;
	void Render() override;

	void SetTime();

private: 

	float timeStep = 0;
	float waitTime = 2;

};

