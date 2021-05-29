#include "Bot.h"
#include "Game.h"
#include "Random.h"
#include "Special.h"
#include <iostream>

Bot::Bot(Game* game)
	: Character(game, "Bot")
	, mCurrentState(E0)
{

}

void Bot::UpdateActor(float deltaTime)
{
	AI_State new_state = mCurrentState;

	Character* player = GetGame()->GetOpponent(this);

	float distance = player->GetPosition().x - GetPosition().x;
	distance = distance > 0 ? distance : -1 * distance;

	float rand = Random::GetFloatRange(0, 1);

	switch (mCurrentState)
	{
	case E0:
		if (mHP < 0.3)
			new_state = E7;
		else if (distance > 450)
			new_state = E1;
		else if (distance < 350)
			new_state = E3;
		else
			new_state = E2;
		break;
	case E1:
		RushIn(player, deltaTime);
		new_state = E4;
		break;
	case E2:
		new_state = E4;
		break;
	case E3:
		DrawBack(player, deltaTime);
		new_state = E4;
		break;
	case E4:
		if (rand < 0.03)
			new_state = E5;
		else if (rand < 0.06)
			new_state = E6;
		else
			new_state = E0;
		break;
	case E5:
		Attack(player, deltaTime);
		new_state = E0;
		break;
	case E6:
		Jump();
		new_state = E0;
		break;
	case E7:
		if (distance > 600)
			new_state = E8;
		else
			new_state = E9;
		break;
	case E8:
		RushIn(player, deltaTime);
		new_state = E10;
		break;
	case E9:
		DrawBack(player, deltaTime);
		new_state = E10;
		break;
	case E10:
		if (rand < 0.08)
			new_state = E11;
		else if (rand < 0.12)
			new_state = E12;
		else
			new_state = E7;
		break;
	case E11:
		Attack(player, deltaTime);
		new_state = E7;
		break;
	case E12:
		Jump();
		new_state = E7;
		break;
	default:
		break;
	}

	mCurrentState = new_state;
}



void Bot::DrawBack(Character* player, float deltaTime)
{
	Vector2 current_pos = GetPosition();
	Vector2 direction = (player->GetPosition() - current_pos).x > 0 ? Vector2(1, 0) : Vector2(-1, 0);
	current_pos += Vector2(300, 0) * direction * deltaTime;

	SetDirection(direction);

	applyForce(Vector2(2, 0) * direction * -1);
}

void Bot::RushIn(Character* player, float deltaTime)
{
	Vector2 current_pos = GetPosition();
	Vector2 direction = (player->GetPosition()- current_pos).x > 0 ? Vector2(1, 0) : Vector2(-1, 0);
	current_pos += Vector2(300, 0) * direction * deltaTime;

	SetDirection(direction);

	applyForce(Vector2(2, 0) * direction);
}

void Bot::Attack(Character* player, float deltaTime)
{
	new Special(GetGame(), this);
}

void Bot::Jump()
{
	if (GetPosition().y > 640)
	{
		applyForce(Vector2(0, -450.0f));
	}
}
