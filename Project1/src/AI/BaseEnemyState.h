#pragma once
#include "eStates.h"
class Enemy;
class BaseEnemyState
{
public:
	BaseEnemyState() {};
	virtual ~BaseEnemyState() {};
	virtual void StartState()= 0;
	virtual void UpdateState(float deltatime)=0;
	virtual void ExitState()= 0 ;
	virtual void Render() = 0;
     void ChangeState(eStates state);

	 Enemy* enemy;
};

