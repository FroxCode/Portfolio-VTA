#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "SDL.h"

class Observer
{
public:
	Observer() {}
	~Observer() {}

	virtual void Update(bool ach, SDL_Renderer* renderer) = 0;

private:

};
