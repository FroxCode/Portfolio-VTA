#pragma once
#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>

class statScreen
{
public:
	statScreen();
	//startScreen(SDL_Renderer* r);
	~statScreen();
	void Render(SDL_Renderer* r);
	int getSelectedItem() { return selectedItem; }
	bool getDisplay() { return display; }
	void setDisplay();
	void updateStats(SDL_Renderer* r, int hp, float att, float agi, float def);
	void intialise(SDL_Renderer* r);

private:
	SDL_Texture* m_texture;
	TTF_Font* font;
	bool display;
	SDL_Surface* textSurface[8];
	SDL_Rect textBox[8];
	SDL_Texture* text[8];
	SDL_Rect background;
	std::string convToString(float val);

	int selectedItem;
	SDL_Color white = { 255,255,255 };



};