// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
:MoveComponent(owner)
,mForwardKey(0)
,mBackwardKey(0)
,mJumpKey(0)
,mDuckKey(0)
,mMaxHorizontalSpeed(0)
,mMaxVerticalSpeed(0)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate horizontal speed for MoveComponent
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxHorizontalSpeed;
	}
	if (keyState[mBackwardKey])
	{
		forwardSpeed -= mMaxHorizontalSpeed;
	}
	SetSpeed(forwardSpeed);

	// Calculate vertical speed for MoveComponent
	float verticalSpeed = 0.0f;
	if (keyState[mJumpKey])
	{
		;
	}
	if (keyState[mDuckKey])
	{
		;
	}
	//SetVerticalSpeed(verticalSpeed);
}
