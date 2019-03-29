
#ifndef IDLE_H_
#define IDLE_H_

#include "State.h"
#include "AKState.h"
#include "ShotgunState.h"
#include "DeagleState.h"
//States
#include <thread>
#include <chrono>

class AKState;
class DeagleState;
class ShotgunState;

class Idle : public State
{
public:
	Idle() { std::cout << "Idle" << std::endl; };
	~Idle() {  };

	bool aking(FSM* a)
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
	bool idle(FSM* a)
	{
		//Do deagle stuff
		return true;
	}
	
};



#endif // !
