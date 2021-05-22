// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
	mRect = new SDL_Rect();
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		auto flip = mOwner->GetDirection().x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		// Scale the width/height by owner's scale
		mRect->w = static_cast<int>(mTexWidth * mOwner->GetScale());
		mRect->h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		mRect->x = static_cast<int>(mOwner->GetPosition().x - mRect->w / 2);
		mRect->y = static_cast<int>(mOwner->GetPosition().y - mRect->h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			mRect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			flip);

		//SDL_RenderCopyEx(render, mTexture, NULL, mRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
