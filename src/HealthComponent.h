#pragma once
#include "Component.h"

class HealthComponent : public Component
{
private:
	int health = 50;
	int maxHealth = 100;
	bool isAlive = true;
	int kills = 0;
	int deaths = 0;
	int playerID = 0;

public:
	HealthComponent() : health(100), Component("Health"){}
	~HealthComponent() {};
	int getHealth(){ return health; }
	int getMaxHealth() { return maxHealth; }
	void setHealth(int health) { this->health = health; }
	void setMaxHealth(int h) { this->maxHealth = h; }
	bool getAlive() { return isAlive; }
	void setAlive(bool set) { isAlive = set; }

	int getKillCount() { return kills; }
	void setKillCount(int killCount) { kills = killCount; }
	int getDeathCount() { return deaths; }
	void setDeathCount(int deathCount) { deaths = deathCount; }


	int getPlayerID() { return playerID; }
	void setPlayerID(int newPlayerID) { playerID = newPlayerID; }
};