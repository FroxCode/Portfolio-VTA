#include "OnlineSystem.h"



OnlineSystem::OnlineSystem() {}

void OnlineSystem::init(std::string ip, int port)
{
	std::string ipc = ip;
	int portc = 5050;
	ver = MAKEWORD(2, 2);
	wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "CAN'T START WINSOCK" << std::endl;
		WSACleanup();
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket" << std::endl;
		WSACleanup();
	}

	hint.sin_family = AF_INET;
	hint.sin_port = htons(portc);
	inet_pton(AF_INET, ipc.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't create socket" << std::endl;
		closesocket(sock);
		WSACleanup();
	}

	id = "(NULL)";
}


OnlineSystem::~OnlineSystem()
{
}
void OnlineSystem::addEntity(Entity &e) {

	entities.push_back(&e);

}
void OnlineSystem::update(SDL_Renderer* r, gameStates state)
{
	if (state.mpState == gameStates::MP_LOBBY) {
		userInput = "(GIVEID)";
		int startX = 0;
		int startY = 0;
		int sendResult = send(sock, userInput.c_str(), userInput.size(), 0);
		if (sendResult != SOCKET_ERROR)
		{
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				std::stringstream ss(std::string(buf, 0, bytesReceived));
				ss >> id >> pNumber >> playerCount;
				for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++) {
					if ((*i)->getTag() == "Player")
					{
						for (int j = 0; j < (*i)->getComponents().size(); j++)
						{
							if ((*i)->getComponents().at(j)->getID() == "Health")
							{
								if (static_cast<HealthComponent*>((*i)->getComponents().at(j))->getPlayerID() == 0)
								{
									static_cast<HealthComponent*>((*i)->getComponents().at(j))->setPlayerID(pNumber);
								}
							}
							else if ((*i)->getComponents().at(j)->getID() == "Position")
							{
								switch (pNumber)
								{
								case 1: 
									startX = 128;
									startY = 128;
									break;
								case 2:
									startX = 1280 - 192;
									startY = 128;
									break;
								case 3: 
									startX = 128;
									startY = 1280 - 192;
									break;
								case 4: 
									startX = 1280 - 192;
									startY = 704 - 192;
									break;
								default:
									break;
								}
								static_cast<PositionComponent*>((*i)->getComponents().at(j))->setPosition(SDL_Point() = {startX, startY});
							}
						}
					}
				}
			}
		}
	}
	else if (state.mpState == gameStates::MP_PLAYING) {
		if (counter > 3)
		{
			counter = 0;
			sendPlayerData();
		}
		else
		{
			counter++;
		}
		for (int i = 0; i < 4; i++)
		{
			std::cout << playerID[i] << std::endl;
			std::cout << pX[i] << ", " << pY[i] << std::endl;
			std::cout << angle[i] << std::endl;
			std::cout << fired[i] << std::endl;
			std::cout << "Kills: " << killCount[i] << std::endl;
			std::cout << "Deaths: " << deathCount[i] << std::endl;
		}
		int pNum = 1;
		for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++) {
			if ((*i)->getTag() == "OnlinePlayer") {
				for (std::vector<Entity*>::iterator p = entities.begin(), e = entities.end(); p != e; p++) {
					if ((*p)->getTag() == "Player") {
						for (int c = 0; c < (*p)->getComponents().size(); c++) {
							if ((*p)->getComponents().at(c)->getID() == "Health") {
								if (pNum != static_cast<HealthComponent*>((*p)->getComponents().at(c))->getPlayerID()) {
									//update dummies
									for (int dC = 0; dC < (*i)->getComponents().size(); dC++)
									{
										if ((*i)->getComponents().at(dC)->getID() == "Position")
										{
											static_cast<PositionComponent*>((*i)->getComponents().at(dC))->setPosition(SDL_Point() = { pX[pNum - 1], pY[pNum - 1] });
										}
										else if ((*i)->getComponents().at(dC)->getID() == "Online")
										{
											static_cast<OnlineComponent*>((*i)->getComponents().at(dC))->setAngle(angle[pNum - 1]);
										}
										else if ((*i)->getComponents().at(dC)->getID() == "Health")
										{
											static_cast<HealthComponent*>((*i)->getComponents().at(dC))->setKillCount(killCount[pNum - 1]);
											static_cast<HealthComponent*>((*i)->getComponents().at(dC))->setDeathCount(deathCount[pNum - 1]);
										}
										else if ((*i)->getComponents().at(dC)->getID() == "Firing")
										{
											if (fired[pNum - 1] != 0)
											{
												if (static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getCanFire())
												{

													if (static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getTimer() - static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getFireRate() > 0)
													{
														static_cast<FiringComponent*>((*i)->getComponents().at(dC))->setTimer(static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getTimer() -
															static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getFireRate());
													}
													else
													{
														for (int j = 0; j < (*i)->getComponents().size(); j++)
														{
															if ((*i)->getComponents().at(j)->getID() == "Position")
															{
																SDL_Rect rect;
																rect.x = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().x + 16;
																rect.y = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().y + 16;
																rect.h = 32;
																rect.w = 32;
																for (int m = 0; m < (*i)->getComponents().size(); m++) {
																	if ((*i)->getComponents().at(m)->getID() == "Graphics") {

																		switch (static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getCurrentGun())
																		{
																		case 1:
																			m_bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getDamage(), "Enemy"));
																			break;
																		case 2:
																			m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 260, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getDamage(), "Enemy"));
																			m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getDamage(), "Enemy"));
																			m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 280, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getDamage(), "Enemy"));
																			break;
																		default:
																			m_bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(dC))->getDamage(), "Enemy"));
																			break;
																		}
																	}
																}
															}

															static_cast<FiringComponent*>((*i)->getComponents().at(dC))->setTimer(100);
														}
													}
												}
											}
										}
									}
								}
								else if(pNum == static_cast<HealthComponent*>((*p)->getComponents().at(c))->getPlayerID())
								{
									for (int pC = 0; pC < (*i)->getComponents().size(); pC++)
									{
										if ((*i)->getComponents().at(pC)->getID() == "Position")
										{
											static_cast<PositionComponent*>((*i)->getComponents().at(pC))->setPosition(SDL_Point() = { pX[pNum - 1], pY[pNum - 1] });
										}
									}
								}
							}
						}
					}
				}
			}
			pNum++;
		}
	}	
}
void OnlineSystem::sendPlayerData()
{
	PlayerData myPlayer;
	
	for (std::vector<Entity*>::iterator p = entities.begin(), e = entities.end(); p != e; p++) {
		if ((*p)->getTag() == "Player") {
			for (int c = 0; c < (*p)->getComponents().size(); c++) {
				if ((*p)->getComponents().at(c)->getID() == "Health") {
					myPlayer.playerID = static_cast<HealthComponent*>((*p)->getComponents().at(c))->getPlayerID();
					myPlayer.killCount = static_cast<HealthComponent*>((*p)->getComponents().at(c))->getKillCount();
					myPlayer.deathCount = static_cast<HealthComponent*>((*p)->getComponents().at(c))->getDeathCount();
				}
				else if ((*p)->getComponents().at(c)->getID() == "Position") {
					myPlayer.px = static_cast<PositionComponent*>((*p)->getComponents().at(c))->getPosition().x;
					myPlayer.py = static_cast<PositionComponent*>((*p)->getComponents().at(c))->getPosition().y;
				}
				else if ((*p)->getComponents().at(c)->getID() == "Control") {
					myPlayer.angle = static_cast<ControlComponent*>((*p)->getComponents().at(c))->getAngle();
				}
				else if ((*p)->getComponents().at(c)->getID() == "Firing") {
					myPlayer.fired = static_cast<FiringComponent*>((*p)->getComponents().at(c))->fired;
				}
			}
		}
	}


	int sendResult = send(sock, (char *)&myPlayer, sizeof(PlayerData), 0);
	
	
	if (sendResult != SOCKET_ERROR)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		if (bytesReceived > 0) //ss >> id >> PX, PY, ROT, FIRED, kills, deads 
		{
			std::stringstream ss(std::string(buf, 0, bytesReceived));
			ss >> id >> playerID[0] >> pX[0] >> pY[0] >> angle[0] >> fired[0] >> killCount[0] >> deathCount[0] >>
				playerID[1] >> pX[1] >> pY[1] >> angle[1] >> fired[1] >> killCount[1] >> deathCount[1] >>
				playerID[2] >> pX[2] >> pY[2] >> angle[2] >> fired[2] >> killCount[2] >> deathCount[2] >>
				playerID[3] >> pX[3] >> pY[3] >> angle[3] >> fired[3] >> killCount[3] >> deathCount[3];
		}
	}
}

int OnlineSystem::getPlayerCount()
{
	return playerCount;
}
int OnlineSystem::getMyPlayerNumber()
{
	return pNumber;
}