#include "Lasers.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Lasers::Lasers(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	// Store the textures 
	asc->SetAnimLoop(false);
	std::vector<std::vector<SDL_Texture*>> anims = {
		{
			game->GetTexture("Assets/Laser.png")
		}
	};
	asc->SetAnimTextures(anims);	
}

void Lasers::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += 250.0f * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x > 1024.0f)
	{
		this->SetState(EDead);
	}
	SetPosition(pos);
	Game* game = this->GetGame();
 	game->IsEnemyHit(this);
}
