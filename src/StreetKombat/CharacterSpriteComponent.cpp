#include "CharacterSpriteComponent.h"

//
//CharacterSpriteComponent::CharacterSpriteComponent(Actor* owner, int drawOrder)
//{
//
//}

void CharacterSpriteComponent::Update(float deltaTime)
{
}

void CharacterSpriteComponent::SetMovingTextures(const std::vector<SDL_Texture*>& textures)
{
	mMovingTextures = textures;
	if (mMovingTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mMovingTextures[0]);
	}
}

void CharacterSpriteComponent::SetStoppedTexture(SDL_Texture* texture)
{
	mStoppedTexture = texture;

}
