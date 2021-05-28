#pragma once
#include "Character.h"
class Bot :
    public Character
{
public:
  Bot(class Game* game);

	enum AI_State
	{
		E0, E1, E2, E3,  E4,  E5, E6,
		E7, E8, E9, E10, E11, E12
	};

private:
	void UpdateActor(float deltaTime) override;

	void DrawBack(Character* player, float deltaTime);
	void RushIn(Character* player, float deltaTime);
	void Attack(Character* player, float deltaTime);
	void Jump();

	AI_State mCurrentState;
};

