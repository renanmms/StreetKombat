// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"
#include <stdio.h>

InputComponent::InputComponent(class Actor* owner)
:PhysicsComponent(owner)
,mForwardKey(0)
,mBackwardKey(0)
,mJumpKey(0)
,mDuckKey(0)
,mSpeed(Vector2(0,0))
,mWalkSpeed(Vector2(300,0))
,isJumping(false)
,isPunching(false)
,punchCooldown(0)
,punchDelay(0)
{
	
}

void InputComponent::Update(float deltaTime)
{
	punchCooldown -= deltaTime;
	if (isPunching) {
		punchDelay += deltaTime;
	}
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
	isJumping = !(mOwner->GetPosition().y == 650.0f);
	
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
	//std::cout << "punchCooldown: " << punchCooldown << std::endl;
	//std::cout << "punchDelay: " << punchDelay << std::endl << std::endl;
	
	if (keyState[mPunchKey] && punchCooldown <= 0)
	{
		isPunching = true;
		punchCooldown = 1;
	}
	if (punchDelay > 1)
	{
		punchDelay = 0;
		// TO-DO Socar
		printf("Entrou no ProcessInput\n");
	}
	else {
		isPunching = false;
		punchDelay = 0;
		punchCooldown = 0;
	}
	
	mSpeed = mOwner->GetDirection()*currentSpeed;
	
	// Calculate vertical speed for MoveComponent
	float verticalSpeed = 0.0f;
	if (keyState[mJumpKey] && // Se apertou a tecla pra pular
			!isJumping) // Não é a tecla pra pular que continua apertada
	{
		mOwner->applyForce(Vector2(0, -250.0f));
	}

	
}