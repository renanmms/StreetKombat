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
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetBackwardKey(SDL_SCANCODE_A);
	ic->SetForwardKey(SDL_SCANCODE_D);
	ic->SetJumpKey(SDL_SCANCODE_W);
	ic->SetDuckKey(SDL_SCANCODE_S);
	ic->SetMaxHorizontalSpeed(300.0f);
	ic->SetMaxVerticalSpeed(300.0f);
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
