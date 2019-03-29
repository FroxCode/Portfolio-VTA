#pragma once

#include <iostream>
#include <memory>
#include "SDL.h"
#include "GraphicsComponent.h"

class FSM
{
	class State* current;
public:
	FSM();
	~FSM();
	//static_cast<GraphicsComponent*>(player->getComponents().at(4))
	void initialise(GraphicsComponent* g);
	void setCurrent(int s);
	void idle();
	void ak();
	void shotgun();
	void deagle();

	GraphicsComponent* m_graphics;

private:
	
};
