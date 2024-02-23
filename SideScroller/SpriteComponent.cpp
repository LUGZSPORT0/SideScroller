#include "Actor.h"
#include "Game.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	// adds itself to a vector of sprite components in the Game class via the Game::AddSprite function
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter
		SDL_RenderCopyEx(renderer,						// Render target to draw to	
			mTexture,									// Texture to draw
			nullptr,									// Part of texture to draw (null if whole)
			&r,											// Rectangle to draw onto the target
			-Math::ToDegrees(mOwner->GetRotation()),	// Rotation angle (in degrees, clockwise)
			nullptr, 									// Point to rotate about (nullptr for center)
			SDL_FLIP_NONE); 							// How to flip texture (usually SDL_FLIP_NONE)
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}