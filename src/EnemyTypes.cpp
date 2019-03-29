#include "EnemyTypes.h"


Entity* EnemyTypes::SpeedEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints)
{
	enemyPath = "assets/enemy1.png";
	enemyType = new Entity("Enemy");
	enemyType->addComponent(new HealthComponent());
	enemyType->addComponent(new PositionComponent(rand() % 4, spawnPoints));
	enemyType->addComponent(new FiringComponent("deagle"));
	enemyType->addComponent(new GraphicsComponent(enemyPath, r));
	int enemyHealth = 60;
	float enemyAttack = 1;
	float enemyDefense = 1;
	float enemyAgility = 15;
	enemyType->addComponent(new StatsComponent(enemyHealth, enemyAttack, enemyDefense, enemyAgility));
	return enemyType;
}

Entity * EnemyTypes::TankEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints)
{
	enemyPath = "assets/enemy2.png";
	enemyType = new Entity("Enemy");
	enemyType->addComponent(new HealthComponent());
	enemyType->addComponent(new PositionComponent(rand() % 4, spawnPoints));
	enemyType->addComponent(new FiringComponent("shotgun"));
	enemyType->addComponent(new GraphicsComponent(enemyPath, r));
	int enemyHealth = 200;
	float enemyAttack = 1;
	float enemyDefense = 8;
	float enemyAgility = 1;
	enemyType->addComponent(new StatsComponent(enemyHealth, enemyAttack, enemyDefense, enemyAgility));
	return enemyType;
}

Entity * EnemyTypes::NormalEnemy(int choiceNum, SDL_Renderer * r, SDL_Point spawnPoints)
{
	enemyPath = "assets/enemy3.png";
	enemyType = new Entity("Enemy");
	enemyType->addComponent(new HealthComponent());
	enemyType->addComponent(new PositionComponent(rand() % 4, spawnPoints));
	enemyType->addComponent(new FiringComponent("ak"));
	enemyType->addComponent(new GraphicsComponent(enemyPath, r));
	int enemyHealth = 120;
	float enemyAttack = 3;
	float enemyDefense = 3;
	float enemyAgility = 3;
	enemyType->addComponent(new StatsComponent(enemyHealth, enemyAttack, enemyDefense, enemyAgility));
	return enemyType;
}

