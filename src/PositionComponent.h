#pragma once
#include "Component.h"

class PositionComponent : public Component
{
private:
	SDL_Point position = { 0, 0 };
	int direction;
	SDL_Point velocity = { 0,0 };
	std::vector<SDL_Point> waypoints;
	bool flee = false;
	bool wander = true;

public:
	PositionComponent() : Component("Position") {}
	PositionComponent(int dir, SDL_Point pos) : Component("Position") { position = pos; direction = dir; }
	~PositionComponent() {};

	SDL_Point getPosition()
	{
		return position;
	}
	void setPosition(SDL_Point newPosition)
	{
		position = newPosition;
	}
	int getDirection()
	{
		return direction;
	}
	void setDirection(int newDirection) { this->direction = newDirection; }

	void setFlee() 
	{
		if (!flee)
		{
			flee = true;
		}
		if (flee)
		{
			flee = false;
		}
	}

	bool getFlee() { return flee; }

	SDL_Point getWaypoint(int i)
	{
		return waypoints.at(i);
	}

	void setWaypoints()
	{
		waypoints.push_back(SDL_Point{ 100,100 });
		waypoints.push_back(SDL_Point{ 1000,100 });
		waypoints.push_back(SDL_Point{ 1000,550 });
		waypoints.push_back(SDL_Point{ 100,550 });
	}

	void setWander(bool set) { wander = set; }


	bool getWander() { return wander; }
};