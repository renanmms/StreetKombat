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
:PhysicsComponent(owner)
,mForwardKey(0)
,mBackwardKey(0)
,mJumpKey(0)
,mDuckKey(0)
,mSpeed(Vector2(0,0))
,mWalkSpeed(Vector2(300,0))
,isJumping(false)
{
	
}

void InputComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();
	pos += mSpeed * deltaTime;
	
	// --- Aplica os limites da tela
	if (pos.x < 0.0f) { pos.x = 0.0f; }
	else if (pos.x > 1024.0f) { pos.x = 1024.0f; }
	if (pos.y < 0.0f) { pos.y = 0.0f; }
	else if (pos.y > 650.0f) { pos.y = 650.0f; }

	mOwner->SetPosition(pos);
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	if (mOwner->GetPosition().y == 650.0f)
		isJumping = false;

	// Calculate horizontal speed for MoveComponent
	Vector2 currentSpeed = Vector2(0,0);
	if (keyState[mForwardKey])
	{
		mOwner->SetDirection(Vector2(1, 0));
		currentSpeed = mWalkSpeed;
	}
	if (keyState[mBackwardKey])
	{
		mOwner->SetDirection(Vector2(-1, 0));
		currentSpeed = mWalkSpeed;
	}
	
	mSpeed = mOwner->GetDirection()*currentSpeed;

	// Calculate vertical speed for MoveComponent
	float verticalSpeed = 0.0f;
	if (keyState[mJumpKey] && // Se apertou a tecla pra pular
			!isJumping) // Não é a tecla pra pular que continua apertada
	{
		mOwner->applyForce(Vector2(0, -250.0f));
		isJumping = true;
	}
}

