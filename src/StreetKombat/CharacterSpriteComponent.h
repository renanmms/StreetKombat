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
	void SetIdlingTexture(SDL_Texture* texture);
	void SetJumpingTextures(const std::vector<SDL_Texture*>& textures);
	void SetAttackTextures(const std::vector<SDL_Texture*>& textures);
	//void SetJumpingTexture(SDL_Texture* texture);

	void SetMovingTextureFPS(float fps) { movingTextureFPS = fps; }
	
	void ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS, bool singleExecution = false);
	void ChangeTexture(SDL_Texture* staticTexture);

private:
	enum state {
		STATE_MOVING,
		STATE_IDLING,
		STATE_JUMPING,
		STATE_PUNCH
	};
	// All textures in the animation
	std::vector<SDL_Texture*> mMovingTextures;
	SDL_Texture* mIdlingTexture;
	//SDL_Texture* mJumpingTexture;
	std::vector<SDL_Texture*> mJumpingTextures;
	std::vector<SDL_Texture*> mPunchTextures;
	// Current frame displayed
	float mCurrFrame;

	float movingTextureFPS;

	InputComponent* mInput;

	AnimSpriteComponent* animatedSprite;
	SpriteComponent* staticSprite;

	state current_state;
	
};

