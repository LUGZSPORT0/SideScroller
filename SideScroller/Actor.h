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
	const Vector2 &GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	bool GetAllowDamage() { return mTakeDamage; }
	void SetAllowDamage(bool takeDamage) { mTakeDamage = takeDamage; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;
	
	Vector2 mPosition;
	float mScale;
	float mRotation;
	bool mTakeDamage;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};