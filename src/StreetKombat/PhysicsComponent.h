// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Math.h"

class PhysicsComponent : public Component
{
public:
	// Lower update order to update first
	PhysicsComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;
	
	Vector2 GetSpeed() const { return mSpeed; }
private:
	// Controls forward movement (units/second)
	Vector2 mSpeed;
};
