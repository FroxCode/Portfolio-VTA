#ifndef STATE_H_
#define STATE_H_
#include "FSM.h"

class State
{
public:

	virtual bool idle(FSM* a)
	{
		//std::cout << "State::Idling" << std::endl;
		return true;
	}

	virtual bool aking(FSM* a)
	{
		//std::cout << "State::AK" << std::endl;
		return true;
	}
	virtual bool shotgunning(FSM* a)
	{
		//std::cout << "State::Shotgun" << std::endl;
		return true;
	}
	virtual bool deagling(FSM* a)
	{
		//std::cout << "State::Deagle" << std::endl;
		return true;
	}

};
#endif // !STATE_H_