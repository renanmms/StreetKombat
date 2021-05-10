// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
	
	// Getters/setters for private variables
	float GetMaxHorizontal() const { return mMaxHorizontalSpeed; }
	float GetMaxVertical() const { return mMaxVerticalSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackwardKey; }
	int GetJumpKey() const { return mJumpKey; }
	int GetDuckKey() const { return mDuckKey; }

	void SetMaxHorizontalSpeed(float speed) { mMaxHorizontalSpeed = speed; }
	void SetMaxVerticalSpeed(float speed) { mMaxVerticalSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetJumpKey(int key) { mJumpKey = key; }
	void SetDuckKey(int key) { mDuckKey = key; }
private:
	// The maximum speeds
	float mMaxHorizontalSpeed;
	float mMaxVerticalSpeed;
	// Keys for horizontal movement
	int mForwardKey;
	int mBackwardKey;
	// Keys for vertical movement
	int mJumpKey;
	int mDuckKey;
};
