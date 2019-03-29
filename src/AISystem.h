#pragma once
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "FiringComponent.h"
#include "GraphicsComponent.h"
#include "Bullet.h"
#include "Entity.h"
#include "DecisionTree.h"
#include <memory>

class AISystem
{
private:
	Decision Dead;
	Decision LowHealth;
	Decision BeingAttacked;
	Decision Trapped;
	Decision NearbyEnemies;
	Decision Previous;
	Decision Enemies;
	Decision Strongest;
	Action Wait;
	Action Heal;
	Action PanicAttack;
	Action Attack;
	Action Flee;
	Action Ignore;
	Action Search;

	SDL_Point p;
	SDL_Point playerPos;
	SDL_Point targetPos;
	SDL_Point allyPos;
	SDL_Point bossPos;
	SDL_Point sourcePos;
	SDL_Point enemyPos;
	float vx;
	float vy;
	float dis;
	float m_linearX = 0;
	float m_linearY = 0;
	int waypointIndex = 0;
	const float m_maxspeed = 5;
	const float m_maxAcceleration = 25.0f;
	const float m_radiusStop = 30;
	const float m_radiusSlow = 200;
	const float m_radiusNotice = 400;
	const float m_maxaccel = 5;
	float m_VelX;
	float m_VelY;
	std::vector<Entity *> entities;
	int direction;
	float magnitude;
	float timer = 100;
	
	SDL_Point boundsX = { 0, 1280 - 256 };
	SDL_Point boundsY = { 0, 704 - 256 };
	SDL_Point vel = {1, 1};

	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> bullets;
	bool revive = false;

	int bossStage = 1;

public:
	AISystem() 
	{
		Dead.setName("Dead");
		LowHealth.setName("LowHealth");
		BeingAttacked.setName("BeingAttacked");
		Trapped.setName("Trapped");
		NearbyEnemies.setName("NearbyEnemies");
		Previous.setName("Previous");
		Enemies.setName("Enemies");
		Strongest.setName("Strongest");
		Wait.setName("Wait");
		Heal.setName("Heal");
		PanicAttack.setName("PanicAttack");
		Attack.setName("Attack");
		Flee.setName("Flee");
		Ignore.setName("Ignore");
		Search.setName("Search");

		Strongest.addChild(&Attack, true);
		Strongest.addChild(&Ignore, false);
		Previous.addChild(&Attack, true);
		Previous.addChild(&Strongest, false);
		Enemies.addChild(&Search, true);
		Enemies.addChild(&Heal, false);
		NearbyEnemies.addChild(&Previous, true);
		NearbyEnemies.addChild(&Enemies, false);
		Trapped.addChild(&PanicAttack, true);
		Trapped.addChild(&Flee, false);
		BeingAttacked.addChild(&Trapped, true);
		BeingAttacked.addChild(&Heal, false);
		LowHealth.addChild(&BeingAttacked, true);
		LowHealth.addChild(&NearbyEnemies, false);
		Dead.addChild(&Wait, true);
		Dead.addChild(&LowHealth, false);
	}
	void addEntity(Entity &e);
	void update(SDL_Renderer* r);
	void addBullet(std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> b) { bullets = b; }
	float GetMagnitude(float x, float y)
	{
		float m = sqrt((x * x) + (y * y));

		return m;
	}



};
