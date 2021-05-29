// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Header deste codigo
#include "Game.h"
// Dependencias do SDL
#include "SDL/SDL_image.h"
// Actors
#include "Actor.h"
#include "Character.h"
#include "Bot.h"
// Components
#include "AnimSpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "SpecialComponent.h"
// Utils
#include "Random.h"
// Bibliotecas
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "CharacterSpriteComponent.h"


Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
,player_1(DEEJAY)
,player_2(DEEJAY)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Street Kombat", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	Random::Init();

	//LoadMenu();
	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);


	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	float hp_player = mPlayer1->getHP() > 0 ? mPlayer1->getHP() : 0;
	float hp_bot = mBot->getHP() > 0 ? mBot->getHP() : 0;


	char* player_name;
	int player_width;

	char* bot_name;
	int bot_width;

	player_name = player_1 == HAGGAR ? "haggar" :
		player_1 == DEEJAY ? "deejay" :
		player_1 == CODY ? "cody" :
		"";

	bot_name = player_2 == HAGGAR ? "haggar" :
		player_2 == DEEJAY ? "deejay" :
		player_2 == CODY ? "cody" :
		"";

	player_width = player_1 == HAGGAR ? 160 :
		player_1 == DEEJAY ? 145 :
		player_1 == CODY ? 110 :
		0;

	bot_width = player_2 == HAGGAR ? 160 :
		player_2 == DEEJAY ? 145 :	
		player_2 == CODY ? 110 :
		0;

	drawLifeBar(hp_player, 50, 50, 300);
	drawText(SDL_GetWindowSurface(mWindow), 55, 50, player_width, 30, player_name);

	drawLifeBar(hp_bot, 650, 50, 300);
	drawText(SDL_GetWindowSurface(mWindow), 655, 50, bot_width, 30, bot_name);


	SDL_RenderPresent(mRenderer);
}

void Game::drawLifeBar(float hp, int pos_x, int pos_y, int width)
{

	// contorno
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_Rect contorno{
		static_cast<int>(pos_x - 4), // x
		static_cast<int>(pos_y - 5), // y
	width+8,
	38
	};
	SDL_RenderFillRect(mRenderer, &contorno);

	// background
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_Rect bg{
		static_cast<int>(pos_x),
		static_cast<int>(pos_y),
	width,
	30
	};

	SDL_RenderFillRect(mRenderer, &bg);

	// HP

	if (hp > 0.7)
		SDL_SetRenderDrawColor(mRenderer, 63, 154, 40, 255);

	else if (hp > 0.4)
		SDL_SetRenderDrawColor(mRenderer, 187, 230, 87, 255);
	else
		SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

	SDL_Rect bar{
		static_cast<int>(pos_x),
		static_cast<int>(pos_y),
	hp * width,
	30
	};

	SDL_RenderFillRect(mRenderer, &bar);

}

void Game::drawText(SDL_Surface* screen, int x, int y, int w, int h, char* texto)
{
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w;
	dstrect.h = h;

	SDL_Color color = { 255,255,255 };

	TTF_Init();

	TTF_Font* font = TTF_OpenFont("ARCADECLASSIC.ttf", 50);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, texto, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);


	SDL_RenderCopy(mRenderer, textTexture, NULL, &dstrect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
	TTF_Quit();
}

void Game::LoadData()
{
	// ------ CHAO E PAREDES ------ \\
	// --- Chao
	Actor* ground = new Actor(this);
	ground->SetPosition(Vector2(512.0f, 760));
	mGround = new BoundingBoxComponent(ground, 1024.0f, 16.0f);
	// --- Vetor das paredes
	mWalls = std::vector<BoundingBoxComponent*>();
	// --- Parede esquerda
	Actor* left_wall = new Actor(this);
	left_wall->SetPosition(Vector2(5.0f, 384.0f));
	mWalls.push_back(new BoundingBoxComponent(left_wall, 10.0f, 768.0f));
	// --- Parede direita
	Actor* right_wall = new Actor(this);
	left_wall->SetPosition(Vector2(1019.0f, 384.0f));
	mWalls.push_back(new BoundingBoxComponent(left_wall, 10.0f, 768.0f));

	// ------ PLAYER 1 ------ \\
	// --- Cria o personagem do jogador 1
	mPlayer1 = new Character(this, "Player1");
	mPlayer1->SetPosition(Vector2(512.0f, 384.0f));

	// --- Movimenta��o do player 1 (p1)
	InputComponent* ic = new InputComponent(mPlayer1);
	ic->SetBackwardKey(SDL_SCANCODE_A);
	ic->SetForwardKey(SDL_SCANCODE_D);
	ic->SetJumpKey(SDL_SCANCODE_W);
	ic->SetDuckKey(SDL_SCANCODE_S);
	ic->SetPunchKey(SDL_SCANCODE_SPACE);
	// --- Aplica gravidade a p1
	PhysicsComponent* pc_p1 = new PhysicsComponent(mPlayer1);
	// --- Cria a sprite
	CharacterSpriteComponent* player1_sprite = new CharacterSpriteComponent(ic, 150);
	player1_sprite->LoadCharacter(player_1);
	// --- Cria um golpe especial para o jogador 1
	std::vector<int> sequencia_p1 = {
		SDL_SCANCODE_L,
		SDL_SCANCODE_K,
		SDL_SCANCODE_L,
		SDL_SCANCODE_J
	};
	new SpecialComponent(mPlayer1, sequencia_p1);

	// ------ BOT ------ \\
	// --- Cria personagem do bot
	mBot = new Bot(this);
	mBot->SetPosition(Vector2(812.0f, 384.0f));
	// --- Aplica gravidade a p1
	PhysicsComponent* pc_bot = new PhysicsComponent(mBot);
	// --- Inputs do bot
	InputComponent* bot_ic = new InputComponent(mBot);
	bot_ic->SetBackwardKey(SDL_SCANCODE_1);
	bot_ic->SetForwardKey(SDL_SCANCODE_2);
	bot_ic->SetJumpKey(SDL_SCANCODE_3);
	bot_ic->SetDuckKey(SDL_SCANCODE_4);
	// --- Cria a sprite
	CharacterSpriteComponent* bot_sprite = new CharacterSpriteComponent(bot_ic, 150);
	bot_sprite->LoadCharacter(player_2);
	// --- cria um golpe especial para o bot
	std::vector<int> sequencia_bot = {
		SDL_SCANCODE_O,
		SDL_SCANCODE_I,
		SDL_SCANCODE_Y,
		SDL_SCANCODE_U
	};
	new SpecialComponent(mBot, sequencia_bot);

	// ------ BACKGROUND ------ \\
	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));

	// Create the "far back" background
	AnimSpriteComponent* bg = new AnimSpriteComponent(temp);
	//create a vector
	std::vector<SDL_Texture*> bgtexs = std::vector<SDL_Texture*>();
	for (int i = 0; i < 15; i++) {
		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << i;
		std::string s = ss.str();
		bgtexs.push_back(GetTexture("Assets/Backgrounds/Ship/Background_ship_" + s + "_delay-0.15s.gif"));
	}
	//set this vector to the background component
	bg->SetAnimTextures(bgtexs);
	bg->SetAnimFPS(6.66f); // 1/0.15s

	this->mBackground = temp;
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

Character* Game::GetOpponent(class Character* player)
{
	// Player 2 e Bot n�o podem jogar um contra o outro, 
	// entao se for um destes o adversario � o player 1
	if (player == mPlayer2 || player == mBot)
		return mPlayer1;
	// Player 2 e Bot n�o podem jogar ao mesmo tempo,
	// ent�o se player for player 1, quem n�o for null � o adversario
	if (mPlayer2 != nullptr)
	{
		return mPlayer2;
	}
	return mBot;
}

const BoundingBoxComponent Game::GetGround()
{
	return *mGround;
}

const std::vector<BoundingBoxComponent*> Game::GetWalls() {
	return mWalls;
}

SDL_Renderer* Game::GetRenderer()
{
	return mRenderer;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end())
		mSprites.erase(iter);
}

/*void Game::LoadMenu()
{
	// mostra o menu inicial

	SDL_Surface* screen = SDL_GetWindowSurface( mWindow );
	Uint32 black = SDL_MapRGB(screen->format, 0, 0, 0);
	Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
	SDL_FillRect(screen, NULL, black);
	SDL_UpdateWindowSurface(mWindow);

	SDL_Texture* menu_game_logo = GetTexture("Assets/Fighters/fighter_idle.png");



}*/