#pragma once
#include "Component.h"

class ControlComponent : public Component
{
private:
	SDL_Point velocity = { 0, 0 };
	double angle = 0;
	const int MAX_VELOCITY_X = 10;//need to be edited for pickups
	const int MAX_VELOCITY_Y = 10;
public:
	ControlComponent() : Component("Control")
	{
		angle = 300;
	};
	~ControlComponent() {};

	double getAngle() 
	{ 
		return angle; 
	}
	void setAngle(double a) 
	{ 
		angle = a; 
	}

	SDL_Point getVelocity() { return velocity; }
	void setVelocity(SDL_Point newV) {
		this->velocity = newV;
		if (this->velocity.x > MAX_VELOCITY_X)
			this->velocity.x = MAX_VELOCITY_X;
		if (this->velocity.y > MAX_VELOCITY_Y)
			this->velocity.y = MAX_VELOCITY_Y;

	}

	std::string currentMessage = "(UPDATE)";
};