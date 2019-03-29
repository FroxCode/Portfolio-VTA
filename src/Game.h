#pragma once


#include <iostream>
#include "SDL.h"
#include "GraphicsSystem.h"
#include "ControlSystem.h"
#include "AISystem.h"
#include "Entity.h"
#include "Grid.h"
#include "Bullet.h"
#include <memory>
#include "GraphicsComponent.h"
#include <ctime>
#include "StartScreen.h"
#include "GameStates.h"
#include "HUD.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Rooms.h"
#include "OptionsScreen.h"
#include "MultiplayerScreen.h"
#include "MapGeneration.h"
#include "StatScreen.h"
#include "StatsComponent.h"
#include "Experience.h"
#include "DecisionTree.h"
#include "Item.h"
#include "OnlineSystem.h"
#include "OnlineComponent.h"
#include "Achievement.h"
#include "Subject.h"
#include "Observer.h"
#include "AchievementList.h"
#include "Spawner.h"
#include "EnemyTypes.h"
#include "SDL_mixer.h"
#include "FSM.h"


/** The game objct whic manages the game loop*/
class Game
{
private:
	bool pause;
	bool quit;

	//Multiplayer test
	

	const int PLAYER_WIDTH = 64;
	const int PLAYER_HEIGHT = 64;
	unsigned int lastTime;//time of last update;

	PositionComponent* playerPositionComponent;
	PositionComponent* enemyPositionComponent;
	PositionComponent* allyPositionComponent;
	PositionComponent* bossPositionComponent;
	HealthComponent* bossHealthComponent;
	ExperienceComponent* experienceComponent;
	StatsComponent* playerStatsComponent;
	StatsComponent* allyStatsComponent;
	CollisionManager cManager;
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	std::vector<std::shared_ptr<Bullet>> bullets;
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> b;

	gameStates gameState;
	InputController* controller;
	bool startBossMusic = true;
	SDL_Texture* winScreen;
	SDL_Texture* deathScreen;
	SDL_Rect winSize = { 0, 0, 1280, 704 };
	SDL_Window * window;
	SDL_Surface* icon;
	SDL_Renderer * sdl_renderer;
	MapGeneration* map;
	Grid* world;
	bool doorsLocked;

	Entity* player;
	std::vector<Entity*> onlinePlayers;
	Entity* enemy;
	Entity* ally;
	Entity* boss;
	Spawner* enemyPool;
	std::vector<Entity*> enemyEntities;
	bool erasedEnemy = false;
	std::string enemyPath;
	std::string playerPath;
	std::string allyPath;
	std::string bossPath;

	AISystem aiSystem;
	ControlSystem controlSystem;
	GraphicsSystem graphicsSystem;
	OnlineSystem onlineSystem;
	std::vector<std::shared_ptr<Item>> droppedItems;

	std::vector<bool> achievements;
	std::shared_ptr<std::vector<bool>> a;
	AchievementList achievementList;

	//game achievements
	Achievement reviveMe;
	Achievement firstKill;
	Achievement newRoom;
	Achievement bossRoom;
	Achievement useBoost;
	Achievement newWeapon;
	Achievement noDrop;
	Achievement velvetThunder;
	Achievement deadEnd;
	Achievement levelUp;


	Mix_Music *music_Menu;
	Mix_Music *music_Game;
	Mix_Music *music_Boss;





	HUD hud;
	std::shared_ptr<HUD> m_hud;

	startScreen start;
	std::shared_ptr<startScreen> m_startScreen;

	optionsScreen options;
	std::shared_ptr<optionsScreen> m_optionsScreen;

	multiplayerScreen multiplayer;
	std::shared_ptr<multiplayerScreen> m_multiplayerScreen;

	statScreen stats;
	std::shared_ptr<statScreen> m_statsScreen;


	SDL_Event e;

	

	double temp = 0;

	LTimer fpsTimer;
	LTimer capTimer;
	int countedFrames = 0;


	double xp;
	int m_lvl = 0;
	int maxTemp;

	int magSize = 100;
	int currentBullets = 100;

	//int reviveAlly = 0;
	//int killEnemy = 1;
	//int newRoom = 2;
	//int bossRoom = 3;
	//int firstBoost = 4;
	//int newWeapon = 5;
	//int noDrop = 6;
	//int velvetThunder = 7;
	//int deadEnd = 8;
	//int levelUp = 9;

	//bool firstKill = false;
	bool isOnline = false;
	bool firstTimeSetup = true; //setup for online

	std::vector<SDL_Point> spawnPoints;
	SDL_Point position1 = { 500, 500 };
	SDL_Point position2 = { 200, 500 };
	SDL_Point position3 = { 600, 100 };
	SDL_Point position4 = { 100, 600 };
	SDL_Point position5 = { 200, 400 };
	SDL_Point position6 = { 1000, 200 };


	FSM *fsm;

public:
	Game();
	~Game();

	bool init();

	void destroy();

	void update();
	void render();
	void loop();
	void checkCollision();
	void spawnEnemies();
	void spawnEnemies(bool isBossRoom);
	void checkForLoot(SDL_Point dropPosition);

};