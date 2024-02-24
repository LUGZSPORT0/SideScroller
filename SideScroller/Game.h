#pragma once
#include "SDL.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "Math.h"

class Game
{
public:
	Game();
	// Every game has these three basic functions
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void IsEnemyHit(class Lasers* laser);
	SDL_Texture* GetTexture(const std::string& fileName);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

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

	// Game specific
	//class Ship* mShip; // Player's ship
	//class Enemy* mEnemy; // Enemy ship
	class Hero* mHero;

};

