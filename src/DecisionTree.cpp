#include "DecisionTree.h"

std::vector<int> nearbyEntities;
int allyattackedEntities = -1;
int enemyattackedEntities = -1;
SDL_Point targetPos;
SDL_Point sourcePos;
SDL_Point p;
int waypointIndex = 0;
const float m_maxspeed = 5;
const float m_maxAcceleration = 25.0f;
const float m_radiusStop = 30;
const float m_radiusSlow = 200;
const float m_radiusNotice = 400;
const float m_maxaccel = 5;
float m_VelX;
float m_VelY;
float vx;
float vy;
float dis;
float m_linearX = 0;
float m_linearY = 0;
float targetSpeed = 0;
float targetVelocityX = 0;
float targetVelocityY = 0;
float magnitude;

void DTNode::makeDecision(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity)
{
	if (index == 1)
	{
		Decision* decision = static_cast<Decision*>(this);
		decision->makeDecision(entities, entity);
	}
	else if (index == 2)
	{
		Action* action = static_cast<Action*>(this);
		action->makeDecision(entities, entity);
	}
}

void Decision::makeDecision(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity)
{
	bool check;
	if (name == "Dead")
	{
		check = true;
		if ((*entity)->getTag() == "Ally" || (*entity)->getTag() == "Enemy")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Health")
				{
					if (static_cast<HealthComponent*>((*entity)->getComponents().at(j))->getAlive())
					{
						check = false;
						break;
					}
				}
			}
		}
	}
	else if (name == "LowHealth")
	{
		check = false;
		if ((*entity)->getTag() == "Ally" || (*entity)->getTag() == "Enemy")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Health")
				{
					if (static_cast<HealthComponent*>((*entity)->getComponents().at(j))->getHealth() <= 25)
					{
						check = true;
						break;
					}
				}
			}
		}
		if (!check)
		{
			if ((*entity)->getTag() == "Ally")
			{
				for (int o = 0; o < (*entity)->getComponents().size(); o++)
				{
					if ((*entity)->getComponents().at(o)->getID() == "Position")
					{
						if (static_cast<PositionComponent*>((*entity)->getComponents().at(o))->getFlee() == true)
						{
							static_cast<PositionComponent*>((*entity)->getComponents().at(o))->setFlee();
						}
					}
				}
			}
		}
	}
	else if (name == "BeingAttacked" || name == "NearbyEnemies")
	{
		check = false;
		if ((*entity)->getTag() == "Ally")
		{
			for (int j = 0; j <(*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
			if (allyattackedEntities >= 0)
			{
				if (allyattackedEntities < entities.size() - 1)
				{
					for (int j = 0; j < ((entities.at(allyattackedEntities)))->getComponents().size(); j++)
					{
						if (((entities.at(allyattackedEntities)))->getComponents().at(j)->getID() == "Position")
						{
							for (int k = 0; k < (entities.at(allyattackedEntities))->getComponents().size(); k++)
							{
								if ((entities.at(allyattackedEntities))->getComponents().at(k)->getID() == "Health")
								{
									if (static_cast<HealthComponent*>((entities.at(allyattackedEntities))->getComponents().at(k))->getHealth() > 0)
									{
										targetPos = static_cast<PositionComponent*>((entities.at(allyattackedEntities))->getComponents().at(j))->getPosition();
										float magnitude = sqrt(((targetPos.x - sourcePos.x) *
											(targetPos.x - sourcePos.x)) +
											((targetPos.y - sourcePos.y) *
											(targetPos.y - sourcePos.y)));
										if (magnitude < m_radiusNotice)
										{
											check = true;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			if (!check)
			{
				nearbyEntities.clear();
				allyattackedEntities = -1;
				for (int i = 0; i < entities.size(); i++)
				{
					if ((entities.at(i))->getTag() == "Enemy")
					{
						for (int j = 0; j < (entities.at(i))->getComponents().size(); j++)
						{
							if ((entities.at(i))->getComponents().at(j)->getID() == "Position")
							{
								for (int k = 0; k < (entities.at(i))->getComponents().size(); k++)
								{
									if ((entities.at(i))->getComponents().at(k)->getID() == "Health")
									{
										if (static_cast<HealthComponent*>((entities.at(i))->getComponents().at(k))->getHealth() > 0)
										{
											targetPos = static_cast<PositionComponent*>(entities.at(i)->getComponents().at(j))->getPosition();
											float magnitude = sqrt(((targetPos.x - sourcePos.x) *
												(targetPos.x - sourcePos.x)) +
												((targetPos.y - sourcePos.y) *
												(targetPos.y - sourcePos.y)));
											if (magnitude < m_radiusNotice)
											{
												nearbyEntities.push_back(i);
												check = true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if ((*entity)->getTag() == "Enemy")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
			if (enemyattackedEntities >= 0)
			{
				for (int j = 0; j < (entities.at(enemyattackedEntities))->getComponents().size(); j++)
				{
					if ((entities.at(enemyattackedEntities))->getComponents().at(j)->getID() == "Position")
					{
						for (int k = 0; k < (entities.at(enemyattackedEntities))->getComponents().size(); k++)
						{
							if ((entities.at(enemyattackedEntities))->getComponents().at(k)->getID() == "Health")
							{
								if (static_cast<HealthComponent*>((entities.at(enemyattackedEntities))->getComponents().at(k))->getHealth()> 0)
								{
									targetPos = static_cast<PositionComponent*>((entities.at(enemyattackedEntities))->getComponents().at(j))->getPosition();
									float magnitude = sqrt(((targetPos.x - sourcePos.x) *
										(targetPos.x - sourcePos.x)) +
										((targetPos.y - sourcePos.y) *
										(targetPos.y - sourcePos.y)));
									if (magnitude < m_radiusNotice)
									{
										check = true;
										break;
									}
								}
							}
						}
					}
				}
			}
			if (!check)
			{
				nearbyEntities.clear();
				enemyattackedEntities = -1;
				for (int i = 0; i < entities.size(); i++)
				{
					if ((entities.at(i))->getTag() == "Ally" || (entities.at(i))->getTag() == "Player")
					{
						for (int j = 0; j < (entities.at(i))->getComponents().size(); j++)
						{
							if ((entities.at(i))->getComponents().at(j)->getID() == "Position")
							{
								for (int k = 0; k < (entities.at(i))->getComponents().size(); k++)
								{
									if ((entities.at(i))->getComponents().at(k)->getID() == "Health")
									{
										if (static_cast<HealthComponent*>((entities.at(i))->getComponents().at(k))->getHealth() > 0)
										{
											targetPos = static_cast<PositionComponent*>(entities.at(i)->getComponents().at(j))->getPosition();
											float magnitude = sqrt(((targetPos.x - sourcePos.x) *
												(targetPos.x - sourcePos.x)) +
												((targetPos.y - sourcePos.y) *
												(targetPos.y - sourcePos.y)));
											if (magnitude < m_radiusNotice)
											{
												nearbyEntities.push_back(i);
												check = true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (name == "Trapped")
	{
		check = false;
		//not implemented
	}
	else if (name == "Previous")
	{
		int attackedEntities;
		check = false;
		if ((*entity)->getTag() == "Ally")
		{
			attackedEntities = allyattackedEntities;
		}
		else if ((*entity)->getTag() == "Enemy")
		{
			attackedEntities = enemyattackedEntities;
		}
		if (attackedEntities >= 0)
		{
			for (int j = 0; j < (entities.at(attackedEntities))->getComponents().size(); j++)
			{
				if ((entities.at(attackedEntities))->getComponents().at(j)->getID() == "Position")
				{
					targetPos = static_cast<PositionComponent*>((entities.at(attackedEntities))->getComponents().at(j))->getPosition();
					check = true;
					break;
				}
			}
		}
	}
	else if (name == "Enemies")
	{
		check = false;
		if ((*entity)->getTag() == "Enemy")
		{
			check = true;
		}
		else
		{
			for (std::vector<Entity*>::iterator it = entities.begin(), e = entities.end(); it != e; it++)
			{
				if ((*it)->getTag() == "Enemy")
				{
					for (int j = 0; j < (*it)->getComponents().size(); j++)
					{
						if ((*it)->getComponents().at(j)->getID() == "Health")
						{
							if (static_cast<HealthComponent*>((*it)->getComponents().at(j))->getHealth() > 0)
							{
								check = true;
								break;
							}
						}
					}
				}
			}
		}
	}
	else if (name == "Strongest")
	{
		check = false;
		if ((*entity)->getTag() == "Ally")
		{
			allyattackedEntities = nearbyEntities.at(0);
			if (nearbyEntities.size() > 1)
			{
				for (int i = 1; i < nearbyEntities.size(); i++)
				{
					for (int j = 0; j < (entities.at(nearbyEntities.at(i)))->getComponents().size(); j++)
					{
						if ((entities.at(nearbyEntities.at(i)))->getComponents().at(j)->getID() == "Health")
						{
							if (static_cast<HealthComponent*>((entities.at(nearbyEntities.at(i)))->getComponents().at(j))->getHealth() < static_cast<HealthComponent*>((entities.at(allyattackedEntities))->getComponents().at(j))->getHealth())
							{
								allyattackedEntities = i;
							}
						}
					}
				}
			}
			for (int j = 0; j < (entities.at(allyattackedEntities))->getComponents().size(); j++)
			{
				if ((entities.at(allyattackedEntities))->getComponents().at(j)->getID() == "Position")
				{
					targetPos = static_cast<PositionComponent*>((entities.at(allyattackedEntities))->getComponents().at(j))->getPosition();
					check = true;
					break;
				}
			}
		}
		else if ((*entity)->getTag() == "Enemy")
		{
			enemyattackedEntities = nearbyEntities.at(0);
			if (nearbyEntities.size() > 1)
			{
				for (int i = 1; i < nearbyEntities.size(); i++)
				{
					for (int j = 0; j < (entities.at(nearbyEntities.at(i)))->getComponents().size(); j++)
					{
						if ((entities.at(nearbyEntities.at(i)))->getComponents().at(j)->getID() == "Health")
						{
							if (static_cast<HealthComponent*>((entities.at(nearbyEntities.at(i)))->getComponents().at(j))->getHealth() < static_cast<HealthComponent*>((entities.at(enemyattackedEntities))->getComponents().at(j))->getHealth())
							{
								enemyattackedEntities = i;
							}
						}
					}
				}
			}
			for (int j = 0; j < (entities.at(enemyattackedEntities))->getComponents().size(); j++)
			{
				if ((entities.at(enemyattackedEntities))->getComponents().at(j)->getID() == "Position")
				{
					targetPos = static_cast<PositionComponent*>((entities.at(enemyattackedEntities))->getComponents().at(j))->getPosition();
					check = true;
					break;
				}
			}
		}
	}
	if (check)
	{
		this->trueDTNode->makeDecision(entities, entity);
	}
	else
	{
		this->falseDTNode->makeDecision(entities, entity);
	}
}
void Action::doAction(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity)
{
	//std::cout << name << std::endl;
	if (name == "Wait")
	{

	}
	else if (name == "Heal")
	{
		if ((*entity)->getTag() == "Ally")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Health")
				{
					if (static_cast<HealthComponent*>((*entity)->getComponents().at(j))->getHealth() < 100)
					{
						static_cast<HealthComponent*>((*entity)->getComponents().at(j))->setHealth(static_cast<HealthComponent*>((*entity)->getComponents().at(j))->getHealth() + 1);
					}
				}
			}
		}
	}
	else if (name == "PanicAttack")
	{
		//not implemented
	}
	else if (name == "Attack")
	{
		int attackedEntities;
		if ((*entity)->getTag() == "Ally")
		{
			attackedEntities = allyattackedEntities;
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
		}
		else if ((*entity)->getTag() == "Enemy")
		{
			attackedEntities = enemyattackedEntities;
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
		}
		for (int j = 0; j < (entities.at(attackedEntities))->getComponents().size(); j++)
		{
			if ((entities.at(attackedEntities))->getComponents().at(j)->getID() == "Position")
			{

				targetPos = static_cast<PositionComponent*>((entities.at(attackedEntities))->getComponents().at(j))->getPosition();
				float magnitude = sqrt(((targetPos.x - sourcePos.x) *
					(targetPos.x - sourcePos.x)) +
					((targetPos.y - sourcePos.y) *
					(targetPos.y - sourcePos.y)));

				if (magnitude < m_radiusStop && static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
				{
					targetSpeed = 0;
					vx = targetPos.x - sourcePos.x;
					vy = targetPos.y - sourcePos.y;
				}
				else if (magnitude > m_radiusSlow && magnitude < m_radiusNotice)
				{
					targetSpeed = m_maxspeed;
					vx = targetPos.x - sourcePos.x;
					vy = targetPos.y - sourcePos.y;
					static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setWander(false);
				}
				else
				{
					static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setWander(false);
					if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
					{
						targetSpeed = m_maxspeed * (magnitude / m_radiusSlow);
						vx = targetPos.x - sourcePos.x;
						vy = targetPos.y - sourcePos.y;
					}
					else
					{
						targetSpeed = m_maxspeed;
						vx = targetPos.x - sourcePos.x;
						vy = targetPos.y - sourcePos.y;
					}
				}
				if (vx != 0 && vy != 0)
				{
					dis = GetMagnitude(vx, vy);
					vx = vx / dis;
					vy = vy / dis;
				}

				for (int m = 0; m < (*entity)->getComponents().size(); m++)
				{
					if ((*entity)->getComponents().at(m)->getID() == "Graphics")
					{
						if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
						{
							static_cast<GraphicsComponent*>((*entity)->getComponents().at(m))->setAngle((atan2(-vx, vy) * 180 / M_PI));
						}
						else
						{
							static_cast<GraphicsComponent*>((*entity)->getComponents().at(m))->setAngle((atan2(-vx, vy) * 180 / M_PI + 180));
						}
						m_linearX = vx * targetSpeed;
						m_linearY = vy * targetSpeed;
					}
				}

				if (GetMagnitude(m_linearX, m_linearY) > m_maxaccel)
				{
					float mag = GetMagnitude(m_linearX, m_linearY);
					m_linearX = m_linearX / mag;
					m_linearY = m_linearY / mag;

					m_linearX = m_linearX * m_maxaccel;
					m_linearY = m_linearY * m_maxaccel;
				}

				m_VelX = m_linearX;
				m_VelY = m_linearY;
				if (m_VelX < 1 && m_VelX > 0.5)
				{
					m_VelX = 1;
				}
				else if (m_VelX > -1 && m_VelX < -0.5)
				{
					m_VelX = -1;
				}
				if (m_VelY < 1 && m_VelY > 0.5)
				{
					m_VelY = 1;
				}
				else if (m_VelY > -1 && m_VelY < -0.5)
				{
					m_VelY = -1;
				}
				if (m_VelX > m_maxspeed)
				{
					m_VelX = m_maxspeed;
				}
				else if (m_VelX < -m_maxspeed)
				{
					m_VelX = -m_maxspeed;
				}

				if (m_VelY > m_maxspeed)
				{
					m_VelY = m_maxspeed;
				}
				else if (m_VelY < -m_maxspeed)
				{
					m_VelY = -m_maxspeed;
				}
				if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
				{
					p.x = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().x + m_VelX;
					p.y = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().y + m_VelY;
					if (p.x < 100)
					{
						int x = 5;
					}
				}
				else
				{
					p.x = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().x - m_VelX;
					p.y = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().y - m_VelY;
				}
				static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setPosition(p);

			}
		}
		if ((*entity)->getTag() == "Ally" || (*entity)->getTag() == "Enemy")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == true)
					{
						static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setFlee();
					}
				}
			}
		}

		for (int l = 0; l < (*entity)->getComponents().size(); l++)
		{
			if ((*entity)->getComponents().at(l)->getID() == "Firing")
			{
				if (static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getCanFire() == true)
				{
					if (static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getTimer() - static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getFireRate() > 0)
					{
						static_cast<FiringComponent*>((*entity)->getComponents().at(l))->setTimer(static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getTimer() -
							static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getFireRate());
					}
					else
					{
						if (static_cast<FiringComponent*>((*entity)->getComponents().at(l))->getTimer() != 0)
						{
							static_cast<FiringComponent*>((*entity)->getComponents().at(l))->setTimer(0);
						}
					}
				}
			}
		}
	}
	else if (name == "Flee")
	{
		if ((*entity)->getTag() == "Ally" || (*entity)->getTag() == "Enemy")
		{
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
					{
						static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setFlee();
					}
				}
			}
		}

		int attackedEntities;
		if ((*entity)->getTag() == "Ally")
		{
			attackedEntities = allyattackedEntities;
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
		}
		else if ((*entity)->getTag() == "Enemy")
		{
			for (int i = 0; i < entities.size(); i++)
			{
				if (entities.at(i)->getTag() == "Player")
				{
					attackedEntities = i;
					break;
				}
			}
			for (int j = 0; j < (*entity)->getComponents().size(); j++)
			{
				if ((*entity)->getComponents().at(j)->getID() == "Position")
				{
					sourcePos = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition();
				}
			}
		}
		if (attackedEntities >= 0)
		{
			for (int j = 0; j < (entities.at(attackedEntities))->getComponents().size(); j++)
			{
				if ((entities.at(attackedEntities))->getComponents().at(j)->getID() == "Position")
				{

					targetPos = static_cast<PositionComponent*>((entities.at(attackedEntities))->getComponents().at(j))->getPosition();
					targetSpeed = m_maxspeed;
					vx = targetPos.x - sourcePos.x;
					vy = targetPos.y - sourcePos.y;
					dis = GetMagnitude(vx, vy);
					vx = vx / dis;
					vy = vy / dis;

					for (int m = 0; m < (*entity)->getComponents().size(); m++)
					{
						if ((*entity)->getComponents().at(m)->getID() == "Graphics")
						{
							static_cast<GraphicsComponent*>((*entity)->getComponents().at(m))->setAngle((atan2(-vx, vy) * 180 / M_PI + 180));
							m_linearX = vx * targetSpeed;
							m_linearY = vy * targetSpeed;
						}
					}

					if (GetMagnitude(m_linearX, m_linearY) > m_maxaccel)
					{
						float mag = GetMagnitude(m_linearX, m_linearY);
						m_linearX = m_linearX / mag;
						m_linearY = m_linearY / mag;

						m_linearX = m_linearX * m_maxaccel;
						m_linearY = m_linearY * m_maxaccel;
					}

					m_VelX = m_linearX;
					m_VelY = m_linearY;
					if (m_VelX < 1 && m_VelX > 0.5)
					{
						m_VelX = 1;
					}
					else if (m_VelX > -1 && m_VelX < -0.5)
					{
						m_VelX = -1;
					}
					if (m_VelY < 1 && m_VelY > 0.5)
					{
						m_VelY = 1;
					}
					else if (m_VelY > -1 && m_VelY < -0.5)
					{
						m_VelY = -1;
					}
					if (m_VelX > m_maxspeed)
					{
						m_VelX = m_maxspeed;
					}
					else if (m_VelX < -m_maxspeed)
					{
						m_VelX = -m_maxspeed;
					}

					if (m_VelY > m_maxspeed)
					{
						m_VelY = m_maxspeed;
					}
					else if (m_VelY < -m_maxspeed)
					{
						m_VelY = -m_maxspeed;
					}
					p.x = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().x - m_VelX;
					p.y = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().y - m_VelY;
					static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setPosition(p);

				}
			}
		}
	}
	else if (name == "Ignore")
	{
		//does nothing
	}
	else if (name == "Search")
	{
		int attackedEntities;
		if ((*entity)->getTag() == "Ally")
		{
			attackedEntities = allyattackedEntities;
		}

		if ((*entity)->getTag() == "Ally")
		{
			for (int i = 0; i < entities.size(); i++)
			{
				if (entities.at(i)->getTag() == "Enemy")
				{
					allyattackedEntities = i;
				}
			}
			for (int j = 0; j < (entities.at(allyattackedEntities))->getComponents().size(); j++)
			{
				if ((entities.at(allyattackedEntities))->getComponents().at(j)->getID() == "Position")
				{
					targetPos = static_cast<PositionComponent*>((entities.at(allyattackedEntities))->getComponents().at(j))->getPosition();
					break;
				}
			}
		}
		else if ((*entity)->getTag() == "Enemy")
		{
			attackedEntities = enemyattackedEntities;
		}
		for (int j = 0; j < (*entity)->getComponents().size(); j++)
		{
			if ((*entity)->getComponents().at(j)->getID() == "Position")
			{
				targetSpeed = m_maxspeed;
				if ((*entity)->getTag() == "Enemy")
				{
					static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setWander(true);

					if (sourcePos.x > static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).x - 5
						&& sourcePos.x < static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).x + 5
						&& sourcePos.y < static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).y + 5
						&& sourcePos.y > static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).y - 5)
					{
						waypointIndex++;

						if (waypointIndex > 3)
						{
							waypointIndex = 0;
						}
					}
					vx = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).x - sourcePos.x;
					vy = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getWaypoint(waypointIndex).y - sourcePos.y;
				}
				if ((*entity)->getTag() == "Ally")
				{
					targetSpeed = m_maxspeed * (magnitude / m_radiusSlow);
					vx = targetPos.x - sourcePos.x;
					vy = targetPos.y - sourcePos.y;
				}
				for (int m = 0; m < (*entity)->getComponents().size(); m++)
				{
					if ((*entity)->getComponents().at(m)->getID() == "Graphics")
					{
						if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
						{
							static_cast<GraphicsComponent*>((*entity)->getComponents().at(m))->setAngle((atan2(-vx, vy) * 180 / M_PI));
						}
						else
						{
							static_cast<GraphicsComponent*>((*entity)->getComponents().at(m))->setAngle((atan2(-vx, vy) * 180 / M_PI + 180));
						}
						m_linearX = vx * targetSpeed;
						m_linearY = vy * targetSpeed;
					}
				}


				if (GetMagnitude(m_linearX, m_linearY) > m_maxaccel)
				{
					float mag = GetMagnitude(m_linearX, m_linearY);
					m_linearX = m_linearX / mag;
					m_linearY = m_linearY / mag;

					m_linearX = m_linearX * m_maxaccel;
					m_linearY = m_linearY * m_maxaccel;
				}

				m_VelX = m_linearX;
				m_VelY = m_linearY;
				if (m_VelX < 1 && m_VelX > 0.5)
				{
					m_VelX = 1;
				}
				else if (m_VelX > -1 && m_VelX < -0.5)
				{
					m_VelX = -1;
				}
				if (m_VelY < 1 && m_VelY > 0.5)
				{
					m_VelY = 1;
				}
				else if (m_VelY > -1 && m_VelY < -0.5)
				{
					m_VelY = -1;
				}
				if (m_VelX > m_maxspeed)
				{
					m_VelX = m_maxspeed;
				}
				else if (m_VelX < -m_maxspeed)
				{
					m_VelX = -m_maxspeed;
				}

				if (m_VelY > m_maxspeed)
				{
					m_VelY = m_maxspeed;
				}
				else if (m_VelY < -m_maxspeed)
				{
					m_VelY = -m_maxspeed;
				}
				if (static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getFlee() == false)
				{
					p.x = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().x + m_VelX;
					p.y = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().y + m_VelY;
				}
				else
				{
					p.x = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().x - m_VelX;
					p.y = static_cast<PositionComponent*>((*entity)->getComponents().at(j))->getPosition().y - m_VelY;
				}
				static_cast<PositionComponent*>((*entity)->getComponents().at(j))->setPosition(p);
			}
		}
	}
}