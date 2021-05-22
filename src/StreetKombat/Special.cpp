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
	,mDamage(10.4f)
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
	// ------ Update no timer para desaparecer
	mDeathTimer -= deltaTime;
	// ------ Verifica colisao
	// --- Com o oponente
	Character* enemy = GetGame()->GetOpponent(mCaster);
	if (enemy != nullptr && enemy->GetState() == EActive) 
	{
		if (mHitBox->Colide(*(enemy->mHitBox))) 
		{
			enemy->Hit(mDamage);
			SetState(EDead);
		}
	}
	// --- Com o chao e paredes (+ se o tempo de vida expirou)
	const BoundingBoxComponent ground = GetGame()->GetGround();
	const std::vector<BoundingBoxComponent*> walls = GetGame()->GetWalls();
	if (
		mDeathTimer < 0 ||
		mHitBox->Colide(ground) ||
		mHitBox->Colide(*walls[0]) ||
		mHitBox->Colide(*walls[1])
		) {
		SetState(EDead);
	}
}
