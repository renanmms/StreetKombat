#pragma once
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"
class CharacterSpriteComponent :
    public SpriteComponent
{
public:
	CharacterSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overriden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation
	void SetMovingTextures(const std::vector<SDL_Texture*>& textures);
	void SetStoppedTexture(SDL_Texture* texture);
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	// All textures in the animation
	std::vector<SDL_Texture*> mMovingTextures;
	SDL_Texture* mStoppedTexture;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};

