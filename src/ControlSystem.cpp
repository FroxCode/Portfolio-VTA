#include "ControlSystem.h"

SDL_Point m_pos = { 0,0 };
void ControlSystem::update(SDL_Event &evt, SDL_Renderer *r, gameStates& currentState)
{
	for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++)
	{
		for (int j = 0; j < (*i)->getComponents().size(); j++)
		{
			if ((*i)->getComponents().at(j)->getID() == "Stats")
			{
				if (m_hud->getBoostTimer() > 0)
				{
					if (m_hud->getBoostTimer() % 20 == 0)
					{
						if (boostBarColour == 0)
						{
							boostBarColour = 1;
						}
						else
						{
							boostBarColour = 0;
						}
						if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost() == 1)
						{
							if (boostBarColour == 0)
							{
								m_hud->updateBoostColour({ Uint8(0), Uint8(255), Uint8(0),Uint8(255) });
							}
							else
							{
								m_hud->updateBoostColour({ Uint8(0), Uint8(123), Uint8(0),Uint8(255) });
							}
						}
						if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost() == 2)
						{
							if (boostBarColour == 0)
							{
								m_hud->updateBoostColour({ Uint8(255), Uint8(255), Uint8(0),Uint8(255) });
							}
							else
							{
								m_hud->updateBoostColour({ Uint8(255), Uint8(165), Uint8(0),Uint8(255) });
							}
						}
						if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost() == 3)
						{
							if (boostBarColour == 0)
							{
								m_hud->updateBoostColour({ Uint8(255), Uint8(255), Uint8(255),Uint8(255) });
							}
							else
							{
								m_hud->updateBoostColour({ Uint8(148), Uint8(0), Uint8(211),Uint8(255) });
							}
						}
						if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost() == 4)
						{
							if (boostBarColour == 0)
							{
								m_hud->updateBoostColour({ Uint8(255), Uint8(255), Uint8(255),Uint8(255) });
							}
							else
							{
								m_hud->updateBoostColour({ Uint8(0), Uint8(255), Uint8(255),Uint8(255) });
							}
						}
						if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost() == 5)
						{
							if (boostBarColour == 0)
							{
								m_hud->updateBoostColour({ Uint8(255), Uint8(0), Uint8(255),Uint8(255) });
							}
							else
							{
								m_hud->updateBoostColour({ Uint8(148), Uint8(0), Uint8(211),Uint8(255) });
							}
						}
					}
					m_hud->updateBoostTimer();
					m_hud->updateBoostBar();
				}

				if (m_hud->getBoostTimer() == 0)
				{
					static_cast<StatsComponent*>((*i)->getComponents().at(j))->resetActiveBoost();
					m_hud->updateBoost(static_cast<StatsComponent*>((*i)->getComponents().at(j))->getCurrentBoost());
				}
			}
		}
		for (int j = 0; j < (*i)->getComponents().size(); j++)
		{
			if ((*i)->getComponents().at(j)->getID() == "Firing")
			{
				m_hud->updateBullets(static_cast<FiringComponent*>((*i)->getComponents().at(j))->getMagSize(), static_cast<FiringComponent*>((*i)->getComponents().at(j))->getCurrentGun());
				if (static_cast<FiringComponent*>((*i)->getComponents().at(j))->getTimer() - static_cast<FiringComponent*>((*i)->getComponents().at(j))->getFireRate() > 0)
				{
					static_cast<FiringComponent*>((*i)->getComponents().at(j))->setTimer(static_cast<FiringComponent*>((*i)->getComponents().at(j))->getTimer() -
						static_cast<FiringComponent*>((*i)->getComponents().at(j))->getFireRate());
				}
				else if (!static_cast<FiringComponent*>((*i)->getComponents().at(j))->getReady())
				{
					static_cast<FiringComponent*>((*i)->getComponents().at(j))->setReady(true);
				}
			}
		}
		for (int j = 0; j < (*i)->getComponents().size(); j++)
		{
			if ((*i)->getComponents().at(j)->getID() == "Control")
			{
				/*if (newBoostAdded)
				{
				newBoostAdded = false;*/
				static_cast<StatsComponent*>((*i)->getComponents().at(j))->setBoost(bType);
				m_hud->updateBoost(static_cast<StatsComponent*>((*i)->getComponents().at(j))->getCurrentBoost());
				//}
				while (SDL_PollEvent(&evt) != 0) {

					if (currentState.currentState == gameStates::START)
					{
						if (evt.type == SDL_JOYHATMOTION)
						{
							if (evt.jhat.value & SDL_HAT_DOWN)
							{
								m_startScreen->increaseSelectedItem();
							}

							if (evt.jhat.value & SDL_HAT_UP)
							{
								m_startScreen->decreaseSelectedItem();
							}
						}

						else if (evt.type == SDL_JOYBUTTONUP)
						{
							//A button pressed on play button
							if (evt.jbutton.button == 0)
							{
								if (m_startScreen->getSelectedItem() == 0)
								{
									currentState.currentState = gameStates::GAME;
								}

								else if (m_startScreen->getSelectedItem() == 1)
								{
									currentState.currentState = gameStates::MULTIPLAYER;
								}

								else if (m_startScreen->getSelectedItem() == 2)
								{
									currentState.currentState = gameStates::OPTIONS;
								}

								else if (m_startScreen->getSelectedItem() == 3)
								{
									SDL_Quit();
								}
							}
						}
					}

					else if (currentState.currentState == gameStates::OPTIONS)
					{
						if (evt.type == SDL_JOYHATMOTION)
						{
							if (evt.jhat.value & SDL_HAT_DOWN)
							{
								m_optionsScreen->increaseSelectedItem();
							}

							if (evt.jhat.value & SDL_HAT_UP)
							{
								m_optionsScreen->decreaseSelectedItem();
							}
						}
						else if (evt.type == SDL_JOYBUTTONUP)
						{
							//B button pressed
							if (evt.jbutton.button == 1)
							{
								currentState.currentState = gameStates::START;
							}
						}
					}

					else if (currentState.currentState == gameStates::MULTIPLAYER && currentState.mpState != gameStates::MP_PLAYING)
					{
						if (evt.type == SDL_JOYHATMOTION)
						{
							
							
						}
						else if (evt.type == SDL_JOYBUTTONUP)
						{
							//B button pressed
							if (evt.jbutton.button == 0)
							{
								currentState.mpState = gameStates::MP_PLAYING;
							}
							//B button pressed
							if (evt.jbutton.button == 1)
							{
								currentState.currentState = gameStates::START;
							}
						}
					}
					else if (evt.type == SDL_JOYBUTTONUP && currentState.currentState == gameStates::GAMEOVER)
					{
						//A button pressed on play button
						if (evt.jbutton.button == 0)
						{
							currentState.currentState = gameStates::START;
						}
					}
					else if (evt.type == SDL_JOYAXISMOTION && (currentState.currentState == gameStates::GAME || currentState.mpState == gameStates::MP_PLAYING))
					{

						if (evt.jaxis.axis == 0)
						{
							//left of dead zone
							if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE - 1000 || evt.jaxis.value > JOYSTICK_DEAD_ZONE)
							{
								v.x = evt.jaxis.value;
							}
							else
							{
								v.x = 0;
							}
						}
						if (evt.jaxis.axis == 1)
						{
							if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE || evt.jaxis.value > JOYSTICK_DEAD_ZONE)
							{
								v.y = evt.jaxis.value;
							}
							else
							{
								v.y = 0;
							}
						}
						if (v.x != 0)
						{
							p.x = cos((atan2((double)v.y, (double)v.x) * (180 / M_PI))  * 3.14159265 / 180) * 10;
						}
						else
						{
							p.x = 0;
						}
						if (v.y != 0)
						{
							p.y = sin((atan2((double)v.y, (double)v.x) * (180 / M_PI))  * 3.14159265 / 180) * 10;
						}
						else
						{
							p.y = 0;
						}
						//right x-axis 
						if (evt.jaxis.axis == 3)
						{
							//Left of dead zone
							if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE || evt.jaxis.value > JOYSTICK_DEAD_ZONE)
							{
								xDirection = evt.jaxis.value;
								static_cast<ControlComponent*>((*i)->getComponents().at(j))->setAngle((atan2((double)yDirection, (double)xDirection) * (180 / M_PI)) - (90 * 180 / M_PI));
							}
						}
						if (evt.jaxis.axis == 4)
						{
							//bottom of dead zone
							if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE || evt.jaxis.value > JOYSTICK_DEAD_ZONE)
							{
								yDirection = evt.jaxis.value;
								static_cast<ControlComponent*>((*i)->getComponents().at(j))->setAngle((atan2((double)yDirection, (double)xDirection) * (180 / M_PI)) - (90 * 180 / M_PI));

							}
						}

						//bullets
						if (evt.jaxis.axis == 5)
						{
							if (evt.jaxis.value > -32000)
							{
								playerFiring = true;
							}
							else
							{
								playerFiring = false;
							}
						}
						if (playerFiring)
						{
							for (int k = 0; k < (*i)->getComponents().size(); k++)
							{
								if ((*i)->getComponents().at(k)->getID() == "Firing")
								{
									if (static_cast<FiringComponent*>((*i)->getComponents().at(k))->getReady() == true)
									{
										for (int l = 0; l < (*i)->getComponents().size(); l++)
										{
											if ((*i)->getComponents().at(l)->getID() == "Position")
											{
												SDL_Rect rect;
												rect.x = static_cast<PositionComponent*>((*i)->getComponents().at(l))->getPosition().x + 16;
												rect.y = static_cast<PositionComponent*>((*i)->getComponents().at(l))->getPosition().y + 16;
												rect.w = 32;
												rect.h = 32;

												switch (static_cast<FiringComponent*>((*i)->getComponents().at(k))->getCurrentGun())
												{
												case 1:
													m_bullets->push_back(std::make_shared<Bullet>(r, "assets/akBullet.png", 200, rect, static_cast<ControlComponent*>((*i)->getComponents().at(j))->getAngle() + 90, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(k))->getDamage(), "Player"));
													Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(k))->SFX_ak, 0);
													break;
												case 2:
													m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 200, rect, static_cast<ControlComponent*>((*i)->getComponents().at(j))->getAngle() + 80, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(k))->getDamage(), "Player"));
													m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 200, rect, static_cast<ControlComponent*>((*i)->getComponents().at(j))->getAngle() + 90, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(k))->getDamage(), "Player"));
													m_bullets->push_back(std::make_shared<Bullet>(r, "assets/shotgunBullet.png", 200, rect, static_cast<ControlComponent*>((*i)->getComponents().at(j))->getAngle() + 100, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(k))->getDamage(), "Player"));
													Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(k))->SFX_shotgun, 0);
													break;
												default:
													m_bullets->push_back(std::make_shared<Bullet>(r, "assets/deagleBullet.png", 200, rect, static_cast<ControlComponent*>((*i)->getComponents().at(j))->getAngle() + 90, 25.0f, static_cast<FiringComponent*>((*i)->getComponents().at(k))->getDamage(), "Player"));
													Mix_PlayChannel(-1, static_cast<FiringComponent*>((*i)->getComponents().at(k))->SFX_deagle, 0);
													break;
												}
												static_cast<FiringComponent*>((*i)->getComponents().at(k))->updateCurrentMag();
												static_cast<FiringComponent*>((*i)->getComponents().at(k))->setTimer(100);
												static_cast<FiringComponent*>((*i)->getComponents().at(k))->setReady(false);

											}
										}
									}
								}
							}
						}
					}
					else if (evt.type == SDL_JOYBUTTONUP && currentState.currentState == gameStates::GAME)
					{
						for (int j = 0; j < (*i)->getComponents().size(); j++)
						{
							if ((*i)->getComponents().at(j)->getID() == "Stats")
							{
								//Back button pressed
								if (evt.jbutton.button == 6)
								{
									m_statsScreen->setDisplay();
								}
								//LB button pressed
								if (evt.jbutton.button == 4)
								{
									if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getCurrentBoost() != 0)
									{
										static_cast<StatsComponent*>((*i)->getComponents().at(j))->setBoostActive();
										static_cast<StatsComponent*>((*i)->getComponents().at(j))->setBoost(0);
										bType = 0;
										m_hud->updateBoost(static_cast<StatsComponent*>((*i)->getComponents().at(j))->getActiveBoost());
										m_hud->setBoostTimer();
										achievements->at(4) = true;
										if (static_cast<StatsComponent*>((*i)->getComponents().at(j))->getCurrentBoost() == 5)
										{
											achievements->at(7) = true;
											for (int k = 0; k < (*i)->getComponents().size(); k++)
											{
												if ((*i)->getComponents().at(k)->getID() == "Health")
												{
													static_cast<HealthComponent*>((*i)->getComponents().at(j))->setHealth(
														static_cast<HealthComponent*>((*i)->getComponents().at(j))->getMaxHealth());
												}
											}
										}

									}
									//new boost pressed
									if (newBoostAdded)
									{
										newBoostAdded = false;
										static_cast<StatsComponent*>((*i)->getComponents().at(j))->setBoost(bType);
										m_hud->updateBoost(static_cast<StatsComponent*>((*i)->getComponents().at(j))->getCurrentBoost());
									}
								}
							}

						}
					}
					static_cast<ControlComponent*>((*i)->getComponents().at(j))->setVelocity(p);
				}
			}
			else if ((*i)->getComponents().at(j)->getID() == "Position")
			{
				SDL_Point pos;
				for (int k = 0; k < (*i)->getComponents().size(); k++)
				{
					if ((*i)->getComponents().at(k)->getID() == "Control")
					{
						pos.x = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().x + static_cast<ControlComponent*>((*i)->getComponents().at(k))->getVelocity().x;
						pos.y = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().y + static_cast<ControlComponent*>((*i)->getComponents().at(k))->getVelocity().y;
						static_cast<PositionComponent*>((*i)->getComponents().at(j))->setPosition(pos);
					}
				}
			}
		}
	}
}