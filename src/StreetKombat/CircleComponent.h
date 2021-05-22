// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "HitBoxComponent.h"
#include "Math.h"

class CircleComponent : public HitBoxComponent
{
public:
	CircleComponent(class Actor* owner, float radius);
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	bool Colide(const CircleComponent& other);
	bool Colide(const BoundingBoxComponent& other);
private:
	float mRadius;
};
