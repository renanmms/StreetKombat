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
	// Create an input component and set keys/speed
	this->SetScale(2.0f);

	// --- Cria a hitbox
	mHitBox = new BoundingBoxComponent(this, 100, 200);
}

void Character::UpdateActor(float deltaTime)
{
	mHitCooldown -= deltaTime;
	std::cout << name << ": " << mHP << std::endl;
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
	mHP -= damage;
	if (mHP <= 0)
		SetState(EDead);
}
