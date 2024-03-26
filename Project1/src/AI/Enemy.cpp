#include "Enemy.h"
#include "../GraphicsRender.h"
Enemy::Enemy(EnemyInfo& enemy)
{
	enemyInfo = enemy;

	LoadModel("Models/Zombie/zombies.obj");

	transform.SetScale(glm::vec3(0.5f));
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
	AddState(IDLE, new IdleState(this));

	
}



void Enemy::DrawProperties()
{
	Model::DrawProperties();
}

void Enemy::SceneDraw()
{
	Model::SceneDraw();
}

void Enemy::Start()
{
	IntialState(IDLE);

	GetCurrentState()->StartState();
}

void Enemy::Update(float deltaTime)
{
	GetCurrentState()->UpdateState(deltaTime);
}

void Enemy::Render()
{

	//GetCurrentState()->Render();
}

void Enemy::OnDestroy()
{
}

BaseEnemyState* Enemy::GetCurrentState()
{
	return currentState;
}

BaseEnemyState* Enemy::GetState(eStates state)
{
	return listOfEnemyStates[state];
}

void Enemy::IntialState(eStates state)
{
	currentState = listOfEnemyStates[state];

	currentState->StartState();
}

void Enemy::OnStateChange(eStates state)
{
	currentState->ExitState();
	currentState = listOfEnemyStates[state];
	currentState->StartState();
}

void Enemy::AddState(eStates state, BaseEnemyState* enemyState)
{
	std::unordered_map<eStates, BaseEnemyState*> ::iterator it = listOfEnemyStates.find(state);

	if (it == listOfEnemyStates.end())
	{
		listOfEnemyStates[state] = enemyState;

	}
}

void Enemy::RemoveState(eStates state)
{
	std::unordered_map<eStates, BaseEnemyState*> ::iterator it = listOfEnemyStates.find(state);


	if (it != listOfEnemyStates.end())
	{
		listOfEnemyStates.erase(it);
	}
}

void Enemy::SetColor(const glm::vec4& color)
{
	for (std::shared_ptr<Mesh> mesh :  meshes)
	{
		mesh->meshMaterial->material()->SetBaseColor(color);
	}
}

