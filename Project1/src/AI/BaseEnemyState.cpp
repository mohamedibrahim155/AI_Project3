#include "BaseEnemyState.h"
#include "Enemy.h"
void BaseEnemyState::ChangeState(eStates state)
{
	enemy->OnStateChange(state);
}
