// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"
#include "CircleComponent.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mSpeed * deltaTime;
		
		Actor tmp = Actor(*this->mOwner);
		tmp.SetPosition(pos);
		CircleComponent new_pos = CircleComponent(&tmp, 0);

		if (pos.x < 0.0f) { pos.x = 0.0f; }
		else if (pos.x > 1024.0f) { pos.x = 1024.0f; }

		if (pos.y < 0.0f) { pos.y = 0.0f; }

		mOwner->SetPosition(pos);
	}
}
