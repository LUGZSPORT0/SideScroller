#pragma once
#include <vector>

class Game
{
public:
	Game();
	// Every game has these three basic functions
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actors*> mPendingActors;
};

