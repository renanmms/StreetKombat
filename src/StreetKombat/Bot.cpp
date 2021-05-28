#include "Bot.h"
#include "Game.h"

Bot::Bot(Game* game)
	: Character(game, "Bot")
	, mCurrentState(E0)
{

}

void Bot::UpdateActor(float deltaTime)
{
	AI_State new_state = mCurrentState;

	Character* player = GetGame()->GetOpponent(this);

	switch (mCurrentState)
	{
	case E0:
		if (mHP < 0.3) {
			new_state = E7;
		}
	default:
		break;
	}
}
