#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>

class Component
{
private:
	std::string id;

public:
	Component() {}
	Component(std::string newID) { id = newID; }
	~Component() {}

	std::string getID() { return id; }
	void setID(std::string newID) { id = newID; }

};