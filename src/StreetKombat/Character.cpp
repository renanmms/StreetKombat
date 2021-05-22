// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Character.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Special.h"
#include "Game.h"

#include <iostream>

Character::Character(Game* game, std::string name)
	:Actor(game)
	,mHitCooldown(0.0f)
	,mHP(1.0f)
	,name(name)
{
	// Create a sprite component
	stopped_sprite = new SpriteComponent(this, 150);
	stopped_sprite->SetTexture(game->GetTexture("Assets/Fighters/fighter_1.png"));

	//AnimSpriteComponent* walking_sprite = new AnimSpriteComponent(this, 160);
	//std::vector<SDL_Texture*> skilltexs = std::vector<SDL_Texture*>();
	//for (int i = 0; i < 8; i++) {
	//	skilltexs.push_back(game->GetTexture("Assets/DefinitelyNotHadouken/frame_" + std::to_string(i) + "_delay-0.02s.gif"));
	//}
	//walking_sprite->SetAnimTextures(skilltexs);
	//walking_sprite->SetAnimFPS(50.0f);

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetBackwardKey(SDL_SCANCODE_A);
	ic->SetForwardKey(SDL_SCANCODE_D);
	ic->SetJumpKey(SDL_SCANCODE_W);
	ic->SetDuckKey(SDL_SCANCODE_S);
	ic->SetMaxHorizontalSpeed(300.0f);
	ic->SetMaxVerticalSpeed(300.0f);
	this->SetScale(2.0f);
}

void Character::UpdateActor(float deltaTime)
{
	mHitCooldown -= deltaTime;
}

void Character::ActorInput(const uint8_t* keyState)
{
	// Kick Input
	if (keyState[SDL_SCANCODE_K] && mHitCooldown <= 0.0f)
	{
		// TODO: Kick
		// Reset cooldown (half second)
		mHitCooldown = 0.5f;
	}
	// Punch Input
	if (keyState[SDL_SCANCODE_P] && mHitCooldown <= 0.0f)
	{
		// TODO: Punch

		// Reset cooldown (half second)
		mHitCooldown = 0.5f;
	}
}

void Character::Hit(float damage)
{
}
