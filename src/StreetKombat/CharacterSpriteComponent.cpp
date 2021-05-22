#include "CharacterSpriteComponent.h"
#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

//
CharacterSpriteComponent::CharacterSpriteComponent(InputComponent* input,  int drawOrder)
	: SpriteComponent(input->GetActor(), drawOrder)
	
{
	mInput = input;

	empty_texture = input->GetActor()->GetGame()->GetTexture("Assets/empty_sprite.png");
}



void CharacterSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	
	if (keyState[mInput->GetForwardKey()] || keyState[mInput->GetBackKey()])
	{
		ChangeTexture(mMovingTextures, movingTextureFPS);
	}
	else 
	{
		ChangeTexture(mStoppedTexture);
	}
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

void CharacterSpriteComponent::ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS)
{
	if (animatedSprite != nullptr)
	{
		//mOwner->RemoveComponent(animatedSprite);
		std::vector<SDL_Texture*> empty = { empty_texture };
		animatedSprite->SetAnimTextures(empty);
	}

	if (staticSprite != nullptr)
	{
		//mOwner->RemoveComponent(staticSprite);
		staticSprite->SetTexture(empty_texture);
	}

	animatedSprite = new AnimSpriteComponent(mOwner, 150);
	animatedSprite->SetAnimTextures(animatedTexture);
	animatedSprite->SetAnimFPS(FPS);
	
}

void CharacterSpriteComponent::ChangeTexture(SDL_Texture* staticTexture)
{
	if(animatedSprite != nullptr)
	{
		std::vector<SDL_Texture*> empty = {empty_texture};
		animatedSprite->SetAnimTextures(empty);
		//mOwner->RemoveComponent(animatedSprite);
	}

	if (staticSprite != nullptr)
	{
		//mOwner->RemoveComponent(staticSprite);
		staticSprite->SetTexture(empty_texture);
	}

	staticSprite = new SpriteComponent(mOwner, 150);
	staticSprite->SetTexture(staticTexture);
}
