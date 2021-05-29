// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"
#include <iostream>

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
	
	if (keyState[mPunchKey] && punchCooldown <= 0)
	{
		isPunching = true;
		punchCooldown = 0.7;
		std::cout << "PREPARE..." << std::endl;
	}
	if (punchDelay > 0.3)
	{
		punchDelay = 0;
		isPunching = false;
		std::cout << "PUNCH" << std::endl;
		Actor* tmp = new Actor(GetActor()->GetGame());
		tmp->SetPosition(GetActor()->GetPosition() + GetActor()->GetDirection() * Vector2(100, 0));
		CircleComponent* cc = new CircleComponent(tmp, 5);
		
		Character* owner = static_cast<Character*>(GetActor());
		Character* enemy = GetActor()->GetGame()->GetOpponent(owner);
		if (cc->Colide(*(enemy->mHitBox))) {
			enemy->Hit(0.1f);
		}
		tmp->SetState(Actor::EDead);
	}
	
	mSpeed = mOwner->GetDirection()*currentSpeed;
	
	float verticalSpeed = 0.0f;


	if (keyState[mJumpKey] && // Se apertou a tecla pra pular
			!isJumping) // A tecla não estava apertada nas iterações anteriores
	{
		// Aplica força vertical para jogar o personagem para cima
		mOwner->applyForce(Vector2(0, -250.0f));
	}

	
}