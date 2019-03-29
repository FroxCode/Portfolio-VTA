#pragma once
#include "Idle.h"

class Idle;
class AKState;
class ShotgunState;

class DeagleState : public State
{

public:
	DeagleState() {};
	~DeagleState() {};

	bool idle(FSM* a)
	{
		std::cout << "Going from Walking to Idling" << std::endl;
		return false;
	}
	bool aking(FSM* a)
	{
		std::cout << "Loading AK" << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
		return false;
	}
	bool shotgunning(FSM* a)
	{
		std::cout << "Loading Shotgun" << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
		return false;
	}
	bool deagling(FSM* a)
	{
		a->m_graphics->setTexture(IMG_LoadTexture(a->m_graphics->sdl_renderer, "assets/player_deagle.png"));
		return true;
	}
};