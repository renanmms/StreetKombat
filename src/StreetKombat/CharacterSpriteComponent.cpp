#include "CharacterSpriteComponent.h"
#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

CharacterSpriteComponent::CharacterSpriteComponent(InputComponent* input,  int drawOrder)
	: Component(input->GetActor(), drawOrder)
	, current_state(STATE_IDLING)
{
	mInput = input;
}



void CharacterSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	CharacterSpriteComponent::state iteration_state = STATE_IDLING;
	if (mInput->IsJumping())
		iteration_state = STATE_JUMPING;
	else if (keyState[mInput->GetForwardKey()] || keyState[mInput->GetBackKey()])
		iteration_state = STATE_MOVING;

	if (current_state != iteration_state)
	{
		switch (iteration_state)
		{
		case STATE_JUMPING:
			// TODO: Colocar cooldown no pulo
			ChangeTexture(mJumpingTextures, jumpingTextureFPS);
			break;
		case STATE_MOVING:
			ChangeTexture(mMovingTextures, movingTextureFPS);
			break;
		case STATE_IDLING:
			ChangeTexture(mIdlingTexture);
			break;
		default:
			break;
		}
	}
	current_state = iteration_state;
}

void CharacterSpriteComponent::SetMovingTextures(const std::vector<SDL_Texture*>& textures)
{
	mMovingTextures = textures;
}

void CharacterSpriteComponent::SetIdlingTexture(SDL_Texture* texture)
{
	mIdlingTexture = texture;
}

/*void CharacterSpriteComponent::SetJumpingTexture(SDL_Texture* texture)
{
	mJumpingTexture = texture;
}*/

void CharacterSpriteComponent::SetJumpingTextures(const std::vector<SDL_Texture*>& textures)
{
	mJumpingTextures = textures;
}

void CharacterSpriteComponent::ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS)
{
	if (animatedSprite != nullptr)
	{
		mOwner->RemoveComponent(animatedSprite);
		mOwner->GetGame()->RemoveSprite(animatedSprite);
	}

	if (staticSprite != nullptr)
	{
		mOwner->RemoveComponent(staticSprite);
		mOwner->GetGame()->RemoveSprite(staticSprite);
	}


	animatedSprite = new AnimSpriteComponent(mOwner, 150);
	animatedSprite->SetAnimTextures(animatedTexture);
	animatedSprite->SetAnimFPS(FPS);
}

void CharacterSpriteComponent::ChangeTexture(SDL_Texture* staticTexture)
{
	if(animatedSprite != nullptr)
	{
		mOwner->RemoveComponent(animatedSprite);
		mOwner->GetGame()->RemoveSprite(animatedSprite);
	}

	if (staticSprite != nullptr)
	{
		mOwner->RemoveComponent(staticSprite);
		mOwner->GetGame()->RemoveSprite(staticSprite);
	}

	staticSprite = new SpriteComponent(mOwner, 150);
	staticSprite->SetTexture(staticTexture);
}
