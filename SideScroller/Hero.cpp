#include "Hero.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <iostream>

Hero::Hero(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	, mInitiateLoop(false)
{
	std::vector<std::vector<SDL_Texture*>> anims = {
		{
			game->GetTexture("Assets/Character01.png"),
			game->GetTexture("Assets/Character02.png"),	
			game->GetTexture("Assets/Character03.png"),
			game->GetTexture("Assets/Character04.png"),
			game->GetTexture("Assets/Character05.png"),
			game->GetTexture("Assets/Character06.png"),
		},
	};
	asc->SetAnimFPS(6.0f);
	asc->SetAnimTextures(anims);
	asc->SetAnimLoop(false);
}

void Hero::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed;
	pos.y += mDownSpeed;
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 1024.0f)
	{
		pos.x = 1024.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}


void Hero::ProcessKeyboard(const uint8_t* state, SDL_KeyboardEvent* key)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	
	if (key->type == SDL_KEYUP && key->keysym.scancode == SDL_SCANCODE_D)
	{
		printf("Release:- ");
		asc->SetAnimLoop(false);
	}

	//else
	//	printf("Press:- ");
	//// right/left
	//if (key->type == SDL_KEYUP)
	//{
	//	std::cout << "key released";
	//}
	//else
	//	std::cout << "ok";

	if (state[SDL_KEYDOWN])
	{
		std::cout << "ok";
	}
	if (state[SDL_SCANCODE_D])
	{
		std::cout << state;
		asc->SetAnimLoop(true);
		mRightSpeed += 2.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 2.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 3.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 3.0f;
	}
	if (state[SDL_SCANCODE_SPACE])
	{

	}
	if (state[SDL_RELEASED])
	{
		asc->SetAnimLoop(false);
	}
}