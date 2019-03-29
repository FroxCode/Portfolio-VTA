#include "StartScreen.h"
#include <iostream>

startScreen::startScreen()
{
}

startScreen::~startScreen()
{
}

void startScreen::intialise(SDL_Renderer* r)
{
	font = TTF_OpenFont("assets/VCR.ttf", 50);

	SDL_Color white = { 0,0,0 };

	int y = 250;

	selectedItem = 0;


	for (int i = 0; i < 4; i++)
	{
		outline[i].x = 85;
		outline[i].y = y;
		outline[i].w = 155;
		outline[i].h = 80;

		buttons[i].x = 88;
		buttons[i].y = y + 3;
		buttons[i].w = 149;
		buttons[i].h = 74;

		y += 100;
	}

	textBox[0].x = 98;
	textBox[0].y = 255;
	textBox[0].w = 128;
	textBox[0].h = 64;

	textBox[1].x = 98;
	textBox[1].y = 355;
	textBox[1].w = 128;
	textBox[1].h = 64;

	textBox[2].x = 98;
	textBox[2].y = 455;
	textBox[2].w = 128;
	textBox[2].h = 64;

	textBox[3].x = 98;
	textBox[3].y = 555;
	textBox[3].w = 128;
	textBox[3].h = 64;

	windowRect = { 0, 0, 1280, 704 };
	background = IMG_LoadTexture(r, "assets/Menu.png");

	titleRect = { 640 - 338, 220, 678, 265 };
	title = IMG_LoadTexture(r, "assets/VTTitle.png");

	textSurface[0] = TTF_RenderText_Solid(font, "PLAY", white);
	textSurface[1] = TTF_RenderText_Solid(font, "ONLINE", white);
	textSurface[2] = TTF_RenderText_Solid(font, "OPTIONS", white);
	textSurface[3] = TTF_RenderText_Solid(font, "QUIT", white);

	text[0] = SDL_CreateTextureFromSurface(r, textSurface[0]);
	text[1] = SDL_CreateTextureFromSurface(r, textSurface[1]);
	text[2] = SDL_CreateTextureFromSurface(r, textSurface[2]);
	text[3] = SDL_CreateTextureFromSurface(r, textSurface[3]);

}



void startScreen::Render(SDL_Renderer* r)
{
	SDL_RenderCopy(r, background, NULL, &windowRect);
	SDL_RenderCopy(r, title, NULL, &titleRect);
	for (int i = 0; i < 4; i++)
	{
		if (selectedItem  == i)
		{
			SDL_SetRenderDrawColor(r, 66, 198, 255, 255);
			SDL_RenderFillRect(r, &outline[selectedItem]);
			SDL_SetRenderDrawColor(r, 255, 0, 129, 120);
			SDL_RenderFillRect(r, &buttons[i]);
		}

		else
		{
			SDL_SetRenderDrawColor(r, 26, 8, 30, 255);
			SDL_RenderFillRect(r, &outline[i]);
			SDL_SetRenderDrawColor(r, 143, 42, 163, 255);
			SDL_RenderFillRect(r, &buttons[i]);
		}


	}

	for (int i = 0; i < 4; i++)
	{
		SDL_RenderCopy(r, text[i], NULL, &textBox[i]);
	}
}

void startScreen::increaseSelectedItem()
{
	selectedItem++;

	if (selectedItem >= 4)
	{
		selectedItem = 3;
	}
}

void startScreen::decreaseSelectedItem()
{
	selectedItem--;
	if (selectedItem < 0)
	{
		selectedItem = 0;
	}
}