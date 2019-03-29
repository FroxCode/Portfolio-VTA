#include "Controller.h"
#include <iostream>
InputController::InputController()
{
}

bool InputController::Init()
{
	bool sucess = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << "sdl could not initiliase! SDL error: %s\n" << SDL_GetError() << std::endl;
		sucess = false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "warning linear texture filtering not enabled!" << std::endl;
	}
	if (SDL_NumJoysticks() < 1)
	{
		std::cout << "no joysticks connected" << std::endl;
	}
	else
	{
		m_gameController = SDL_JoystickOpen(0);
		if (m_gameController == NULL)
		{
			std::cout << "unable to open controller" << std::endl;
		}
	}
	return sucess;
}
