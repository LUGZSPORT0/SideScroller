#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	// Constructor/destructor
	Actor(class Game* game);
	virtual ~Actor();

	// Update funciton called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the coponents attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition;  }
};