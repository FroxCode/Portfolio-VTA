#pragma once
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "FiringComponent.h"
#include "GraphicsComponent.h"
#include "Entity.h"
#include <memory>
class DTNode
{
public:
	DTNode* parentNode;
	DTNode* trueDTNode; //if True
	DTNode* falseDTNode; //if False
	int index;
	std::string name;
	DTNode() { index = 0; }
	void setName(std::string n)
	{
		name = n;
	}
	void makeDecision(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity);
	void addParent(DTNode* parent)
	{
		parentNode = parent;
	}
	void addChild(DTNode* child, bool tf)
	{
		if (tf)
		{
			trueDTNode = child;
		}
		else
		{
			falseDTNode = child;
		}
		trueDTNode->addParent(this);
	}
	float GetMagnitude(float x, float y)
	{
		float m = sqrt((x * x) + (y * y));

		return m;
	}
};

class Decision : public DTNode
{ 
	//testValue
public:
	Decision() { index = 1; }
	void makeDecision(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity);
};

class Action : public DTNode
{
	void doAction(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity);
public:
	Action() { index = 2; }
	void makeDecision(std::vector<Entity *> entities, std::vector<Entity*>::iterator entity)
	{
		doAction(entities, entity);
	}
};
