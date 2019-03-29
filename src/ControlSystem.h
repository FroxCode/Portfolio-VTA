 #pragma once
#include "ControlComponent.h"
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "Entity.h"
#include "Bullet.h"
#include "HUD.h"
#include "Controller.h"
#include "GameStates.h"
#include "FiringComponent.h"
#include "GraphicsComponent.h"
#include "StatsComponent.h"
#include <memory>
#include "StartScreen.h"
#include "OptionsScreen.h"
#include "MultiplayerScreen.h"
#include "StatScreen.h"
#include "OnlineComponent.h"
#include "OnlineSystem.h"

class ControlSystem
{
	std::vector<Entity *> entities;
	std::shared_ptr<startScreen> m_startScreen;
	std::shared_ptr<optionsScreen> m_optionsScreen;
	std::shared_ptr<multiplayerScreen> m_multiplayerScreen;
	std::shared_ptr<statScreen> m_statsScreen;

	std::shared_ptr<HUD> m_hud;
	SDL_Point p;
	SDL_Point v;
	bool fire = false;
	bool rotate = false;
	bool left, right, up, down;
	int bType = 0;
	int boostBarColour = 0;
	bool newBoostAdded = false;
	bool playerFiring = false;
public :
	void addBoost(int type) { bType = type; newBoostAdded = true; };
	void addBullets(std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> &b) { m_bullets = b; };
	void addEntity(Entity &e) { entities.push_back(&e); }
	void update(SDL_Event &evt, SDL_Renderer *r, gameStates& currentState);
	int xDirection = 0;
	int yDirection = 0;
	double joyStickAngle;
	void getStartScreen(std::shared_ptr <startScreen> S) { m_startScreen = S; }
	void getOptionsScreen(std::shared_ptr<optionsScreen> O) { m_optionsScreen = O; }
	void getMultiplayerScreen(std::shared_ptr<multiplayerScreen> M) { m_multiplayerScreen = M; }
	void getStatsScreen(std::shared_ptr<statScreen> statsS) { m_statsScreen = statsS; }
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> m_bullets;
	
	SDL_Rect rect;
	int sendTimer = 0;
	int sendIndex = 0;
	OnlineSystem* onlineSystem;
	void getHUD(std::shared_ptr<HUD> h) { m_hud = h; };
	std::shared_ptr<std::vector<bool>> achievements;
	void getAch(std::shared_ptr<std::vector<bool>> &a) { achievements = a; }
};