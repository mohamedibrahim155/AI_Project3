#include "MoveToRadiusState.h"
#include "../GraphicsRender.h"
#include "Enemy.h"
MoveToRadiusState::MoveToRadiusState(Enemy* enemy)
{
	this->enemy = enemy;

	center = enemy->transform.position;
}

void MoveToRadiusState::StartState()
{
}

void MoveToRadiusState::UpdateState(float deltatime)
{

}

void MoveToRadiusState::ExitState()
{
}

void MoveToRadiusState::Render()
{
	GraphicsRender::GetInstance().DrawSphere(center, radius, glm::vec4(1,0,0,1),true);
}
