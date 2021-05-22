// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "BoundingBoxComponent.h"
#include "AnimSpriteComponent.h"
#include <string>
class Character : public Actor
{
public:
	Character(class Game* game, std::string name);
	SpriteComponent* stopped_sprite;
	AnimSpriteComponent* walking_sprite;
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	void Hit(float damage);
	BoundingBoxComponent* mHitBox;
private:
	std::string name; // Para aparecer em cima da tela junto com o hp
	float mHitCooldown; // Para n�o spamar o bot�o
	float mHP; // Para calcular quando perde
};