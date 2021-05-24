#pragma once
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
class CharacterSpriteComponent :
    public Component
{
public:
	CharacterSpriteComponent(class InputComponent* input, int drawOrder = 100);
	// Update animation every frame (overriden from component)
	void ProcessInput(const uint8_t* keyState) override;
	// Set the textures used for animation
	void SetMovingTextures(const std::vector<SDL_Texture*>& textures);
	void SetStoppedTexture(SDL_Texture* texture);

	void SetMovingTextureFPS(float fps) { movingTextureFPS = fps; }
	
	void ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS);
	void ChangeTexture(SDL_Texture* staticTexture);

private:
	enum state {
		STATE_MOVING,
		STATE_STOPPED
	};
	// All textures in the animation
	std::vector<SDL_Texture*> mMovingTextures;
	SDL_Texture* mStoppedTexture;
	// Current frame displayed
	float mCurrFrame;

	SDL_Texture* empty_texture;

	float movingTextureFPS;

	InputComponent* mInput;

	AnimSpriteComponent* animatedSprite;
	SpriteComponent* staticSprite;

	state current_state;
	
};

