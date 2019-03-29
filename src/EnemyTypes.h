#pragma once
#include "Spawner.h"

class EnemyTypes : public Spawner
{
public:
	EnemyTypes() {};
	~EnemyTypes() {};
	Entity* EnemyTypes::SpeedEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints);
	Entity* EnemyTypes::TankEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints);
	Entity* EnemyTypes::NormalEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints);
private:

	Entity* enemyType;
	std::string enemyPath;
};