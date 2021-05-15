// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
class Special : public Actor
{
public:
	Special(class Game* game, class Character* caster);

	void UpdateActor(float deltaTime) override;
private:
	class CircleComponent* mCircle;
	class Character* mCaster;
	float mDeathTimer;
};