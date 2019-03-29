#pragma once
#include <iostream>
#include "Achievement.h"
#include <vector>
#include <memory>
#include "SDL.h"


class Subject
{
public:
	Subject() {}
	~Subject() {}
	void Attach(Achievement* achieve);
	void Detach(Achievement* achieve);
	void Notify(std::shared_ptr<std::vector<bool>> ac,SDL_Renderer* renderer);

private:
	std::vector<Achievement*> achievements;
};

