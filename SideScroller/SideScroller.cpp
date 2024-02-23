// SideScroller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}

