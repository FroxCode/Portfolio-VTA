#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class multiplayerScreen
{
public:
	multiplayerScreen();
	//startScreen(SDL_Renderer* r);
	~multiplayerScreen();
	void Render(SDL_Renderer* r);
	int getSelectedItem() { return selectedItem; }
	void intialise(SDL_Renderer* r);
	void increaseSelectedItem();
	void decreaseSelectedItem();
	void setPlayerCount(int pc);
	void setMyNumber(int num);

private:
	SDL_Texture* m_texture;
	TTF_Font* font;

	SDL_Surface* textSurface[7];
	SDL_Rect textBox[7];
	SDL_Texture* text[7];
	SDL_Rect buttons[2];
	SDL_Rect outline[2];

	int selectedItem;

	int playerCount = 0;
	int myNumber = 0;


};
