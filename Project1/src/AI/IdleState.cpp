#include "IdleState.h"
#include "Enemy.h"
IdleState::IdleState(Enemy* _enemy)
{
	this->enemy = _enemy;

	waitTime = enemy->enemyInfo.WaitTime;
}

void IdleState::StartState()
{
	SetTime();
}

void IdleState::ExitState()
{
}

void IdleState::UpdateState(float deltatime)
{
	if (timeStep>= waitTime)
	{
		SetTime();

		ChangeState(MOVE_TO);
	}
	else
	{
		timeStep += deltatime;
	}
}

void IdleState::Render()
{

}

void IdleState::SetTime()
{
	timeStep = 0;
	waitTime = enemy->enemyInfo.WaitTime;

}
