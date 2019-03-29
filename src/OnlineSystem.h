#pragma once
#include "PositionComponent.h"
#include "OnlineComponent.h"
#include "HealthComponent.h"
#include "GraphicsComponent.h"
#include "FiringComponent.h"
#include "ControlComponent.h"
#include "Entity.h"
#include <memory>
#include <string>
#include "GameStates.h"
#include "Bullet.h"
class OnlineSystem
{

private:
	struct PlayerData
	{
		int playerID = 0;
		int px = 0;
		int py = 0;
		int angle = 0;
		int fired = 0;
		int killCount = 0;
		int deathCount = 0;
	};
	std::vector<Entity *> entities;
	
	WSAData data;
	WORD ver;
	int wsResult;
	SOCKET sock;
	sockaddr_in hint;
	int connResult;
	char buf[4096];
	std::string userInput;
	std::string id;
	int playerCount;
	int pNumber;
	bool gameStart = false;


	int counter = 0;
	//online temps
	int playerID[4];
	int pX[4];
	int pY[4];
	int angle[4];
	int fired[4];
	int killCount[4];
	int deathCount[4];
public:
	OnlineSystem();
	~OnlineSystem();

	void init(std::string ip, int port);
	void addEntity(Entity &e);
	void update(SDL_Renderer* r, gameStates state);
	int getPlayerCount();
	int getMyPlayerNumber();
	void addBullets(std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> &b) { m_bullets = b; };
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> m_bullets;
	void sendPlayerData();
	
};

