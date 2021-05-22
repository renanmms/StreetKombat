// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "CircleComponent.h"

CircleComponent::CircleComponent(class Actor* owner, float radius)
:HitBoxComponent(owner)
,mRadius(radius)
{
	
}

float CircleComponent::GetRadius() const
{
	return GetOwner().GetScale() * mRadius;
}

bool CircleComponent::Colide(const CircleComponent& other)
{
	return Intersect(*this, other);
}

bool CircleComponent::Colide(const BoundingBoxComponent& other)
{
	return Intersect(*this, other);
}
