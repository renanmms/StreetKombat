// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "PhysicsComponent.h"
#include <cstdint>

class InputComponent : public PhysicsComponent
{
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
	void Update(float deltaTime) override;

	// Getters/setters for private variables
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackwardKey; }
	int GetJumpKey() const { return mJumpKey; }
	int GetDuckKey() const { return mDuckKey; }
	int GetPunchKey() const { return mPunchKey; }

	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetJumpKey(int key) { mJumpKey = key; }
	void SetDuckKey(int key) { mDuckKey = key; }
	void SetPunchKey(int key) { mPunchKey = key; }
	bool IsJumping() { return isJumping; }
	//bool IsPunching() { return isPunching; }
	
	Actor* GetActor() { return mOwner; }

private:
	// Speeds
	Vector2 mWalkSpeed;
	Vector2 mSpeed;
	// Keys for horizontal movement
	int mForwardKey;
	int mBackwardKey;
	// Keys for vertical movement
	int mJumpKey;
	int mDuckKey;
	int mPunchKey;
	// Controle de pulo
	bool isJumping;
	bool isPunching;

	float punchCooldown;
	float punchDelay;
	
};
