#pragma once
#include <vector>
#include<glm/glm.hpp>
#include "BaseEnemyState.h"

class Enemy;

class MoveState : public BaseEnemyState
{
public:

	MoveState(Enemy* enemy);
	~MoveState() {}

     // Inherited via BaseEnemyState
    void StartState() override;
	void UpdateState(float deltatime) override;
	void ExitState() override;
	void Render() override;
	void SetStartPosition(const glm::vec3& position);
	void SetEndPosition(const glm::vec3& position);

private:

	std::vector<glm::vec3> randomPoints = {glm::vec3(0)};

	glm::vec3 startPosition;
	glm::vec3 endPosition;
	glm::vec3 direction;

	float range = 0.5f;

	float moveSpeed = 2;

	glm::vec3 GetRandomPoint();


	float maxXRange;
	float maxZRange;




};

