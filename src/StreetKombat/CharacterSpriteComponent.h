#pragma once
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
class CharacterSpriteComponent :
    public SpriteComponent
{
public:
	CharacterSpriteComponent(class InputComponent* input, int drawOrder = 100);
	// Update animation every frame (overriden from component)
	void ProcessInput(const uint8_t* keyState) override;
	// Set the textures used for animation
	void SetMovingTextures(const std::vector<SDL_Texture*>& textures);
	void SetStoppedTexture(SDL_Texture* texture);
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	void SetMovingTextureFPS(float fps) { movingTextureFPS = fps; }

private:
	// All textures in the animation
	std::vector<SDL_Texture*> mMovingTextures;
	SDL_Texture* mStoppedTexture;
	// Current frame displayed
	float mCurrFrame;

	SDL_Texture* empty_texture;

	float movingTextureFPS;

	InputComponent* mInput;
	// Animation frame rate
	float mAnimFPS;

	AnimSpriteComponent* animatedSprite;
	SpriteComponent* staticSprite;

	//
	
	void ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS);
	void ChangeTexture(SDL_Texture* staticTexture);
};

