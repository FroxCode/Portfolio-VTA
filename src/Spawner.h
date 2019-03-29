#pragma once
#include "Entity.h"
#include "HealthComponent.h"
#include "StatsComponent.h"
#include "PositionComponent.h"
#include "FiringComponent.h"
#include "GraphicsComponent.h"
#include "OnlineComponent.h"

class Spawner
{
public:

	virtual Entity* SpeedEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints) = 0;
	virtual Entity* TankEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints) = 0;
	virtual Entity* NormalEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints) = 0;

private:

protected:
	Spawner() {};
	~Spawner() {};
};