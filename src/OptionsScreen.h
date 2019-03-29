#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class optionsScreen
{
public:
	optionsScreen();
	~optionsScreen();
	void Render(SDL_Renderer* r);
	int getSelectedItem() { return selectedItem; }
	void intialise(SDL_Renderer* r);
	void increaseSelectedItem();
	void decreaseSelectedItem();

private:
	SDL_Texture* m_texture;
	TTF_Font* font;

	SDL_Surface* textSurface[8];
	SDL_Rect textBox[8];
	SDL_Texture* text[8];
	SDL_Rect Optionsbuttons[4];
	SDL_Rect outline[4];

	int selectedItem;




};
