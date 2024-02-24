#pragma once
#include "Actor.h"
#include "AnimSpriteComponent.h"

class Hero : public Actor
{
public:
	Hero(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state, SDL_KeyboardEvent* key);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
private:
	float mRightSpeed;
	float mDownSpeed;
	bool mInitiateLoop;
};

