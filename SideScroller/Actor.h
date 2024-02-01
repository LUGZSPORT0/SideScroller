#pragma once
class Actor
{
public:
	// Called every frame to update the Actor
	virtual void Update(float deltaTIme);
	// Called every frame to draw the Actor
	virtual void Draw();
};

