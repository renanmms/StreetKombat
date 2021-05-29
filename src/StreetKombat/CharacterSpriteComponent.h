#pragma once
#include "Component.h"
#include "Game.h"
#include <vector>
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include <string>

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
	void SetPunchTextures(const std::vector<SDL_Texture*>& textures);
	//void SetJumpingTexture(SDL_Texture* texture);

	void SetMovingTextureFPS(float fps) { movingTextureFPS = fps; }
	void SetJumpingTextureFPS(float fps) { jumpingTextureFPS = fps; }
	
	void ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS, bool singleExecution = false);
	void ChangeTexture(SDL_Texture* staticTexture);

	struct personagem {
		std::string name;
		int jump_fps;
		int jump;
		int walk_fps;
		int walk;
		int punch;
		int kick;
		int dying;
		int revive;
		int name_width;
	};

	void LoadCharacter(Game::character c);

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
	float jumpingTextureFPS;

	InputComponent* mInput;

	AnimSpriteComponent* animatedSprite;
	SpriteComponent* staticSprite;

	state current_state;
	
};

