// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Special.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Colision.h"
#include "Character.h"

Special::Special(Game* game, class Character* caster)
	:Actor(game)
	,mDeathTimer(1.0f)
	,mCaster(caster)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Special::UpdateActor(float deltaTime)
{
	// If we run out of time, Special is dead
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		// Do we intersect with the opponent?
		Character* opponent = GetGame()->GetOpponent(this->mCaster);
		if (Colision::Intersect(*mCircle, *(opponent->GetHitBox())))
		{
			SetState(EDead);
			opponent->Hit(0.1f); // hit for 10% of the hp
		}
	}
}
