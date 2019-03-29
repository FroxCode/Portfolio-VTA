#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class startScreen 
{
public:
	startScreen();
	//startScreen(SDL_Renderer* r);
	~startScreen();
	void Render(SDL_Renderer* r);
	int getSelectedItem() { return selectedItem; }
	void intialise(SDL_Renderer* r);
	void increaseSelectedItem();
	void decreaseSelectedItem();

private:
	SDL_Texture* m_texture;
	TTF_Font* font;

	SDL_Surface* textSurface[4];
	SDL_Rect textBox[4];
	SDL_Texture* text[4];
	SDL_Rect buttons[4];
	SDL_Rect outline[4];

	SDL_Texture* background;
	SDL_Rect windowRect;

	SDL_Texture* title;
	SDL_Rect titleRect;

	int selectedItem;

	


};
