#pragma once
#include "BaseEnemyState.h"
class Enemy;
class MoveToRadiusState  :public BaseEnemyState
{
public:

	MoveToRadiusState(Enemy* enemy);
	// Inherited via BaseEnemyState
	void StartState() override;

	void UpdateState(float deltatime) override;

	void ExitState() override;

	void Render() override;
private:

	float radius = 0.5f;

	glm::vec3 center = glm::vec3(0);

	glm::vec3 randomPositionInside;

};

