#pragma once
#include "Observer.h"
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_image.h"

class Achievement : public Observer
{
public:
	Achievement();
	~Achievement();
	void Update(bool set,SDL_Renderer* renderer);
	void setName(std::string name, SDL_Renderer* renderer);

private:
	std::string achName;
	SDL_Rect background;
	SDL_Rect achRect;
	SDL_Surface* achSurface;
	SDL_Texture* achText[10];

	//font
	TTF_Font* m_font;
};

