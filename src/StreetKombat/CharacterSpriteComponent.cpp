#include "CharacterSpriteComponent.h"
#include "InputComponent.h"
#include "Actor.h"
#include <iostream>
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
	else if (keyState[mInput->GetPunchKey()]) {
		iteration_state = STATE_PUNCH;
	}


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
		case STATE_PUNCH:
			ChangeTexture(mPunchTextures, 10, true);
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

void CharacterSpriteComponent::SetJumpingTextures(const std::vector<SDL_Texture*>& textures)
{
	mJumpingTextures = textures;
}

void CharacterSpriteComponent::SetAttackTextures(const std::vector<SDL_Texture*>& textures)
{
	mPunchTextures = textures;
}

void CharacterSpriteComponent::ChangeTexture(std::vector<SDL_Texture*> animatedTexture, float FPS, bool singleExecution)
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


	animatedSprite = new AnimSpriteComponent(mOwner, 150, singleExecution);
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

void CharacterSpriteComponent::LoadCharacter(Game::character c)
{
	personagem player;
	switch (c)
	{
	case Game::HAGGAR:
		player.name = "haggar";
		player.jump_fps = 2.5f;
		player.jump = 2;
		player.walk_fps = 10.0f;
		player.walk = 12;
		player.punch = 8;
		player.kick = 3;
		player.dying = 8;
		player.revive = 3;
		player.name_width = 160;
		break;
	case Game::DEEJAY:
		player.name = "deejay";
		player.jump_fps = 8.0f;
		player.jump = 8;
		player.walk_fps = 10.0f;
		player.walk = 5;
		player.punch = 0;
		player.kick = 0;
		player.dying = 0;
		player.revive = 0;
		player.name_width = 165;
		break;
	case Game::CODY:
		player.name = "cody";
		player.jump_fps = 2.5f;
		player.jump = 2;
		player.walk_fps = 10.0f;
		player.walk = 12;
		player.punch = 4;
		player.kick = 3;
		player.dying = 2;
		player.revive = 2;
		player.name_width = 110;
		break;
	}

	// --- Cria textura do personagem parado
	SDL_Texture* idlingtexs = mOwner->GetGame()->GetTexture("Assets/Fighters/" + player.name + "/" + player.name + "_idle.png");
	// --- Cria textura do personagem pulando
	std::vector<SDL_Texture*> jumpingtexs = std::vector<SDL_Texture*>();
	for (int i = 1; i <= player.jump; i++) {
		jumpingtexs.push_back(mOwner->GetGame()->GetTexture("Assets/Fighters/" + player.name + "/" + player.name + "_jump_" + std::to_string(i) + ".png"));
	}
	// --- Cria textura do personagem andando
	std::vector<SDL_Texture*> movingtexs = std::vector<SDL_Texture*>();
	for (int i = 1; i <= player.walk; i++) {
		movingtexs.push_back(mOwner->GetGame()->GetTexture("Assets/Fighters/" + player.name + "/" + player.name + "_walk_" + std::to_string(i) + ".png"));
	}
	// --- Cria textura do personagem batendo
	std::vector<SDL_Texture*> punchingtexs = std::vector<SDL_Texture*>();
	for (int i = 1; i <= player.punch; i++) {
		punchingtexs.push_back(mOwner->GetGame()->GetTexture("Assets/Fighters/" + player.name + "/" + player.name + "_punch_" + std::to_string(i) + ".png"));
	}
	// --- Cria textura do personagem morrendo
	std::vector<SDL_Texture*> dieingtexs = std::vector<SDL_Texture*>();
	for (int i = 1; i <= player.dying; i++) {
		dieingtexs.push_back(mOwner->GetGame()->GetTexture("Assets/Fighters/" + player.name + "/" + player.name + "_death_" + std::to_string(i) + ".png"));
	}

	SetJumpingTextures(jumpingtexs);
	SetMovingTextures(movingtexs);
	SetIdlingTexture(idlingtexs);
	SetMovingTextureFPS(player.walk_fps);
	SetJumpingTextureFPS(player.jump_fps);
	ChangeTexture(idlingtexs);

}
