// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Character.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void drawLifeBar(float hp, int pos_x, int pos_y, int width);
	void drawText(SDL_Surface* screen, int x, int y, int w, int h, char* texto);
	
	SDL_Texture* GetTexture(const std::string& fileName);

	Character* GetOpponent(class Character* player);
	SDL_Renderer* GetRenderer();
	const BoundingBoxComponent GetGround();
	const std::vector<BoundingBoxComponent*> GetWalls();

	enum character {
		HAGGAR,
		DEEJAY,
		CODY
	};

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	//void LoadMenu();
	
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	class Actor* mBackground;

	// Game Characters
	class Character* mPlayer1; // Player 1 - aways playing
	class Character* mPlayer2; // Player 2 - can be playing or not
	class Character* mBot;		 // Bot			 - A.I - can be playing or not

	character player_1;
	character player_2;

	// Ch�o
	BoundingBoxComponent* mGround;
	// Paredes esquerda e direita
	std::vector<BoundingBoxComponent*> mWalls;
};
