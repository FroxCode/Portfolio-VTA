#include "FSM.h"
#include "Idle.h"
#include "AKState.h"
#include "ShotgunState.h"
#include "DeagleState.h"

FSM::FSM()
{

}
FSM::~FSM()
{
}
void FSM::initialise(GraphicsComponent* g)
{
	current = new Idle();
	m_graphics = g;
}
//Sets the state of the 
void FSM::setCurrent(int s)
{
	switch (s)
	{
	case 1:
		current = &DeagleState();
		current->deagling(this);
		break;
	case 2:
		current = &AKState();
		current->aking(this);
		break;
	case 3:
		current = &ShotgunState();
		current->shotgunning(this);
		break;
	default:
		break;
	}	
}

void FSM::idle()
{
	current->idle(this);
}

void FSM::ak()
{
	current->aking(this);
}
void FSM::shotgun()
{
	current->shotgunning(this);
}
void FSM::deagle()
{
	current->deagling(this);

}