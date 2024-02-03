#pragma once
#include "SDL.h"
#include <vector>

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

private:
	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;
	// Track if we're updating actors right now
	bool mUpdatingActors;

};

