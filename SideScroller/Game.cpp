#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "Ship.h"
#include "Hero.h"
#include "Enemy.h"
#include "Lasers.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include <iostream>
#include "TileMapComponent.h"
#include <iostream>
#include <sstream>
#include <fstream>

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
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
		SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::LoadData()
{
	//// Create player's ship
	//mShip = new Ship(this);
	//mShip->SetPosition(Vector2(100.0f, 384.0f));
	//mShip->SetScale(1.0f);

	//// Create enemy ship
	//mEnemy = new Enemy(this);
	//mEnemy->SetPosition(Vector2(900.0f, 384.0f));
	//mEnemy->SetScale(0.755f);

	// Create hero
	mHero = new Hero(this);
	mHero->SetPosition(Vector2(900.0f, 384.0f));
	mHero->SetScale(1);

	//// Create actor for the background (this doesn't need a subclass)
	//Actor* temp = new Actor(this);
	//temp->SetPosition(Vector2(512.0f, 384.0f));

	//// Create the "far back" background
	//BGSpriteComponent* bg = new BGSpriteComponent(temp);
	//bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	//std::vector<SDL_Texture*> bgtexs = {
	//	GetTexture("Assets/Farback01.png"),
	//	GetTexture("Assets/Farback02.png")
	//};
	//bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);

	//// Create the closer background
	//bg = new BGSpriteComponent(temp, 90);
	//bgtexs = {
	//	GetTexture("Assets/Stars.png")
	//};
	//bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-200.0f);

	// Create actor for layer 1 of the tile map
	Actor* tileTemp = new Actor(this);
	tileTemp->SetPosition(Vector2(0.0f, 0.0f));

	// Create Layer 1 tile map
	TileMapComponent* tm = new TileMapComponent(tileTemp,99);
	tm->SetTileSceenSize(Vector2(32.0f, 32.0f)); // sets mTile size
	std::vector<SDL_Texture*> tmtexs = {
		GetTexture("Assets/Tiles.png")
	};
	
	tm->SetReadFile(0);
	tm->ReadFromCSVFile();
	tm->SetTileTextures(tmtexs);

	// Create Layer 2 tile map
	tm = new TileMapComponent(tileTemp, 50);
	tm->SetTileSceenSize(Vector2(32.0f, 32.0f)); // sets mTile size
	tmtexs = {
		GetTexture("Assets/Tiles.png")
	};
	
	tm->SetReadFile(1);
	tm->ReadFromCSVFile();
	tm->SetTileTextures(tmtexs);

	// Create Layer 3 tile map
	tm = new TileMapComponent(tileTemp,25);
	tm->SetTileSceenSize(Vector2(32.0f, 32.0f)); // sets mTile size
	tmtexs = {
		GetTexture("Assets/Tiles.png")
	};

	tm->SetReadFile(2);
	tm->ReadFromCSVFile();
	tm->SetTileTextures(tmtexs);

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
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				const Uint8* state = SDL_GetKeyboardState(NULL);
				SDL_KeyboardEvent* key = &event.key;
				mHero->ProcessKeyboard(state, key);
				break;
		}
	}
	// Made changes to ensure the skelton walked
	//const Uint8* state = SDL_GetKeyboardState(NULL);
	//SDL_KeyboardEvent* key = &event.key;
	//if (state[SDL_SCANCODE_ESCAPE])
	//{
	//	mIsRunning = false;
	//}

	//// Process ship input
	////mShip->ProcessKeyboard(state);
	//mHero->ProcessKeyboard(state, key);
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
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// Draw  all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::IsEnemyHit(class Lasers* laser)
{
	for (auto actor : mActors)
	{
		if ((laser->GetPosition().x >=  actor->GetPosition().x - 20) && (laser->GetPosition().x <= actor->GetPosition().x + 50) &&
			(laser->GetPosition().y >= actor->GetPosition().y - 20) && (laser->GetPosition().y <= actor->GetPosition().y + 20)
			&& actor->GetAllowDamage()==true)
		{
			actor->SetState(actor->EDead);
			laser->SetState(actor->EDead);
		}
	}
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

	// Is the texture already in the map
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
		tex = iter->second;
	else
	{
		// Load an image from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface - convers an SDL_Surface to an SDL_Texture
		// Returns a pointer to an SDL_Texture if successful, otherwise nullptr
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
	// If updating actors, need to add to pending
	if (mUpdatingActors)
		mPendingActors.emplace_back(actor);
	else
		mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors:
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

	// Inserts element before position of itereator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}