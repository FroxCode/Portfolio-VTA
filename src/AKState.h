#pragma once
#include "Idle.h"

class Idle;
class DeagleState;
class ShotgunState;

class AKState : public State
{

public:
	AKState() {};
	~AKState() {};

	bool idle(FSM* a)
	{
		std::cout << "Going from Walking to Idling" << std::endl;
		return false;
	}
	bool shotgunning(FSM* a)
	{
		std::cout << "Loading Shotgun" << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
		return false;
	}
	bool deagling()
	{
		std::cout << "Loading Deagle" << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
		return false;
	}
	bool aking(FSM* a)
	{
		a->m_graphics->setTexture(IMG_LoadTexture(a->m_graphics->sdl_renderer, "assets/player_ak.png"));
		return true;
	}
};
