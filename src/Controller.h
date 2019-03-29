#pragma once
#include "SDL.h"

const int JOYSTICK_DEAD_ZONE = 6000;


class InputController
{
public:
	InputController();
	bool Init();

private:
	SDL_Joystick* m_gameController = NULL;
	

};