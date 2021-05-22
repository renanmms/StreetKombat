// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Special.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Character.h"
#include "CircleComponent.h"

#include <iostream>
#include <vector>

Special::Special(Game* game, class Character* caster)
	:Actor(game)
	,mDeathTimer(2.0f)
	,mCaster(caster)
	,mDamage(0.4f)
{
	// ------ Create the sprite
	AnimSpriteComponent* sc = new AnimSpriteComponent(this, 160);
	std::vector<SDL_Texture*> skilltexs = std::vector<SDL_Texture*>();
	for (int i = 0; i < 8; i++) {
		skilltexs.push_back(game->GetTexture("Assets/DefinitelyNotHadouken/frame_" + std::to_string(i) + "_delay-0.02s.gif"));
	}
	sc->SetAnimTextures(skilltexs);
	sc->SetAnimFPS(50.0f); // 1 / 0.02

	// ------ Create the forward movement
	MoveComponent* mc = new MoveComponent(this);
	mc->SetSpeed(400.0f);

	// ------ Create the colision
	mHitBox = new CircleComponent(this,11);

	// ------ Adjust position and scale
	SetPosition(caster->GetPosition() + Vector2(50, 0));
	this->SetScale(0.45f);
}

void Special::UpdateActor(float deltaTime)
{
	// ------ Update the death timer
	mDeathTimer -= deltaTime;
	// ------ Check colision
	Character* enemy = GetGame()->GetOpponent(mCaster);
	if (mHitBox->Colide(*(enemy->mHitBox))) 
	{
		enemy->Hit(mDamage);
		SetState(EDead);
	}
	// ------ Check if it should be deleted
	if (mDeathTimer <= 0.0f 
		|| GetPosition().x > 1023 // Avoid the special to get stuck on the edge of the screen
		|| GetPosition().x < 1
		|| GetPosition().y > 767
		|| GetPosition().y < 1)
	{
		SetState(EDead);
	}
	//else
	//{
	//	// Do we intersect with the opponent?
	//	Character* opponent = GetGame()->GetOpponent(this->mCaster);
	//	if (Colision::Intersect(*mCircle, *(opponent->GetHitBox())))
	//	{
	//		std::cout << "HIT" << std::endl;
	//		SetState(EDead);
	//		opponent->Hit(0.1f); // hit for 10% of the hp
	//	}
	//}
}
