#include "EnemyStateMachine.h"


EnemyStateMachine::EnemyStateMachine()
{
	
}

BaseEnemyState* EnemyStateMachine::GetCurrentState()
{
	return currentState;
}

BaseEnemyState* EnemyStateMachine::GetState(eStates state)
{
	return listOfEnemyStates[state];
}

void EnemyStateMachine::IntialState(eStates state)
{
	currentState = listOfEnemyStates[state];

	currentState->StartState();
}

void EnemyStateMachine::OnStateChange(eStates state)
{
	currentState->ExitState();
	currentState = listOfEnemyStates[state];
	currentState->StartState();
}

void EnemyStateMachine::AddState(eStates state, BaseEnemyState* enemyState)
{
	std::unordered_map<eStates, BaseEnemyState*> ::iterator it = listOfEnemyStates.find(state);
	
	if (it == listOfEnemyStates.end())
	{
		listOfEnemyStates[state] = enemyState;

	}
}

void EnemyStateMachine::RemoveState(eStates state)
{
	std::unordered_map<eStates, BaseEnemyState*> ::iterator it = listOfEnemyStates.find(state);


	if (it != listOfEnemyStates.end())
	{
		listOfEnemyStates.erase(it);
	}
}
