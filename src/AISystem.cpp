#include "AISystem.h"

void AISystem::update(SDL_Renderer* r) {
	bool alive = false;
	for (int k = 0; k < entities.size(); k++)
	{
		if (entities.at(k)->getTag() == "")
		{
			entities.at(k)->~Entity();
			entities.at(k) = nullptr;
			entities.erase(entities.begin() + k);
			entities.shrink_to_fit();
		}
	}
	for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++) {
		std::string iTag = (*i)->getTag();

		for (int k = 0; k < (*i)->getComponents().size(); k++)
		{
			if ((*i)->getComponents().at(k)->getID() == "Health")
			{
				if (static_cast<HealthComponent*>((*i)->getComponents().at(k))->getHealth() <= 0)
				{
					static_cast<HealthComponent*>((*i)->getComponents().at(k))->setAlive(false);
				}
				
				if (static_cast<HealthComponent*>((*i)->getComponents().at(k))->getHealth() >= 100)
				{
					static_cast<HealthComponent*>((*i)->getComponents().at(k))->setAlive(true);
				}

				if (iTag == "Enemy")
				{
					if (static_cast<HealthComponent*>((*i)->getComponents().at(k))->getHealth() <= 25)
					{
						for (int o = 0; o < (*i)->getComponents().size(); o++)
						{
							if ((*i)->getComponents().at(o)->getID() == "Position")
							{
								static_cast<PositionComponent*>((*i)->getComponents().at(o))->setFlee();
							}
						}

						for (int x = 0; x < (*i)->getComponents().size(); x++)
						{
							if ((*i)->getComponents().at(x)->getID() == "Firing")
							{
								static_cast<FiringComponent*>((*i)->getComponents().at(x))->setCanFire(false);
							}
						}
					}
				}
				else if (iTag == "Boss")
				{
					if (static_cast<HealthComponent*>((*i)->getComponents().at(k))->getHealth() >= 600)
					{
						bossStage = 1;
					}
					else if (static_cast<HealthComponent*>((*i)->getComponents().at(k))->getHealth() >= 300)
					{
						bossStage = 2;
					}
					else
					{
						bossStage = 3;
					}
				}
			}
		}
		for (int n = 0; n < (*i)->getComponents().size(); n++)
		{
			if ((*i)->getComponents().at(n)->getID() == "Position")
			{
				if (iTag == "Enemy")
				{
					static_cast<PositionComponent*>((*i)->getComponents().at(n))->setWaypoints();
				}
				else if (iTag == "Boss")
				{

					switch (bossStage)
					{
					case 1:
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x + (vel.x * 2),
							static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y + (vel.y * 2) }); 
						break;
					case 2:
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x + (vel.x * 4),
							static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y + (vel.y * 4) });
						break;
					case 3:
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x + (vel.x * 6),
							static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y + (vel.y * 6) });
						break;
					default:
						break;
					}
			

					if (static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x <= boundsX.x) //Left
					{
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ boundsX.x, static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y });
						vel.x = -vel.x;
					}
					else if (static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x >= boundsX.y) //Right
					{
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ boundsX.y, static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y });
						vel.x = -vel.x;
					}
					if (static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y >= boundsY.y) //Bottom
					{
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x, boundsY.y - 10 });
						vel.y = -vel.y;
					}
					else if (static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().y <= boundsY.x) //Top
					{
						static_cast<PositionComponent*>((*i)->getComponents().at(n))->setPosition({ static_cast<PositionComponent*>((*i)->getComponents().at(n))->getPosition().x, boundsY.x + 10 });
						vel.y = -vel.y;
					}
				}
			}

		}
		if (iTag == "Ally" || iTag == "Enemy")
		{
			Dead.makeDecision(entities, i);
		}
		for (int g = 0; g < (*i)->getComponents().size(); g++)
		{
			if ((*i)->getComponents().at(g)->getID() == "Health")
			{
				//Check if the entity is alive
				if (static_cast<HealthComponent*>((*i)->getComponents().at(g))->getAlive() == true)
				{
					for (int j = 0; j < (*i)->getComponents().size(); j++)
					{
						if ((*i)->getComponents().at(j)->getID() == "Position")
						{
							if (iTag == "Player")
							{
								playerPos = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition();
							}
							else if (iTag == "Enemy")
							{
								enemyPos = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition();
							}
							else if (iTag == "Ally")
							{
								allyPos = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition();

							}
							else if (iTag == "Boss")
							{
								bossPos = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition();
							}
							if (iTag == "Enemy")
							{
								if (static_cast<PositionComponent*>((*i)->getComponents().at(j))->getWander() ||
									static_cast<PositionComponent*>((*i)->getComponents().at(j))->getFlee())
								{
									for (int x = 0; x < (*i)->getComponents().size(); x++)
									{
										if ((*i)->getComponents().at(x)->getID() == "Firing")
										{
											static_cast<FiringComponent*>((*i)->getComponents().at(x))->setCanFire(false);
										}
									}
								}

								else if (!static_cast<PositionComponent*>((*i)->getComponents().at(j))->getWander())
								{
									for (int x = 0; x < (*i)->getComponents().size(); x++)
									{
										if ((*i)->getComponents().at(x)->getID() == "Firing")
										{
											static_cast<FiringComponent*>((*i)->getComponents().at(x))->setCanFire(true);
										}
									}
								}
							}
						}
					}

					if (iTag == "Enemy")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++) {
							if ((*i)->getComponents().at(l)->getID() == "Firing")
							{
								if (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() == 0)
								{
									SDL_Rect rect;

									rect.x = enemyPos.x + 32;
									rect.y = enemyPos.y + 32;
									rect.h = 24;
									rect.w = 24;


									for (int m = 0; m < (*i)->getComponents().size(); m++) {
										if ((*i)->getComponents().at(m)->getID() == "Graphics") {

											switch (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getCurrentGun())
											{
											case 1:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_ak, 0);
												break;
											case 2:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 260, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 280, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_shotgun, 0);
												break;
											default:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_deagle, 0);
												break;
											}
										}
									}
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setTimer(100);
								}
							}
						}
					}

					else if (iTag == "Ally")
					{

						for (int l = 0; l < (*i)->getComponents().size(); l++)
						{
							if ((*i)->getComponents().at(l)->getID() == "Firing")
							{
								if (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() == 0)
								{
									SDL_Rect rect;
									rect.x = allyPos.x + 50;
									rect.y = allyPos.y + 50;
									rect.h = 32;
									rect.w = 32;
									for (int m = 0; m < (*i)->getComponents().size(); m++) {
										if ((*i)->getComponents().at(m)->getID() == "Graphics") {

											switch (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getCurrentGun())
											{
											case 1:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Player"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_ak, 0);
												break;
											case 2:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 260, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Player"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Player"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 280, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Player"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_shotgun, 0);
												break;
											default:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Player"));
												Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(l))->SFX_deagle, 0);

												break;
											}
										}
									}
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setTimer(100);
								}
							}
						}
					}
					if (iTag == "Boss")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++) {
							if ((*i)->getComponents().at(l)->getID() == "Firing")
							{

								switch (bossStage)
								{
								case 1:
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setCurrentGun("deagle");
									break;
								case 2:
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setCurrentGun("shotgun");
									break;
								case 3:
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setCurrentGun("ak");
									break;
								default:
									break;
								}
								if (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() - static_cast<FiringComponent*>((*i)->getComponents().at(l))->getFireRate() > 0)
								{
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setTimer(static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() -
										static_cast<FiringComponent*>((*i)->getComponents().at(l))->getFireRate());
								}
								else
								{
									if (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() != 0)
									{
										static_cast<FiringComponent*>((*i)->getComponents().at(l))->setTimer(0);
									}
								}

								if (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getTimer() == 0)
								{
									SDL_Rect rect;
									rect.x = bossPos.x + 100;
									rect.y = bossPos.y + 80;
									rect.h = 64;
									rect.w = 64;
								

									for (int m = 0; m < (*i)->getComponents().size(); m++) {
										if ((*i)->getComponents().at(m)->getID() == "Graphics") {

											switch (static_cast<FiringComponent*>((*i)->getComponents().at(l))->getCurrentGun())
											{
											case 0:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 265, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 275, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												break;
											case 1:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 240, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 300, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												break;
											case 2:
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 260, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 270, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 280, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 250, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 600, rect, static_cast<GraphicsComponent*>((*i)->getComponents().at(m))->getAngle() - 290, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(l))->getDamage(), "Enemy"));
												break;
											}
										}
									}
									static_cast<FiringComponent*>((*i)->getComponents().at(l))->setTimer(100);
								}
							}
							if ((*i)->getComponents().at(l)->getID() == "Graphics")
							{
								switch (bossStage)
								{
								case 1:
									static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->setAngle(static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->getAngle() + 2);
									break;
								case 2:
									static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->setAngle(static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->getAngle() - 4);
									break;
								case 3:
									static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->setAngle(static_cast<GraphicsComponent*>((*i)->getComponents().at(l))->getAngle() + 6);
									break;
								default:
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}
void AISystem::addEntity(Entity &e) {

	entities.push_back(&e);

}
