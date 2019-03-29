#include "OptionsScreen.h"

optionsScreen::optionsScreen()
{

}

optionsScreen::~optionsScreen()
{

}

void optionsScreen::intialise(SDL_Renderer* r)
{
	font = TTF_OpenFont("assets/VCR.ttf", 50);

	SDL_Color black = { 0,0,0 };
	SDL_Color white = { 255,255,255 };

	int y = 100;

	selectedItem = 0;


	for (int i = 0; i < 4; i++)
	{
		outline[i].x = 300;
		outline[i].y = y;
		outline[i].w = 200;
		outline[i].h = 100;

		Optionsbuttons[i].x = 310;
		Optionsbuttons[i].y = y + 10;
		Optionsbuttons[i].w = 180;
		Optionsbuttons[i].h = 80;

		y += 150;
	}

	textBox[0].x = 345;
	textBox[0].y = 120;
	textBox[0].w = 100;
	textBox[0].h = 60;

	textBox[1].x = 335;
	textBox[1].y = 270;
	textBox[1].w = 120;
	textBox[1].h = 60;

	textBox[2].x = 340;
	textBox[2].y = 420;
	textBox[2].w = 100;
	textBox[2].h = 60;

	textBox[3].x = 325;
	textBox[3].y = 570;
	textBox[3].w = 140;
	textBox[3].h = 60;



	textBox[4].x = 1000;
	textBox[4].y = 120;
	textBox[4].w = 100;
	textBox[4].h = 60;

	textBox[5].x = 1000;
	textBox[5].y = 270;
	textBox[5].w = 120;
	textBox[5].h = 60;

	textBox[6].x = 1000;
	textBox[6].y = 420;
	textBox[6].w = 100;
	textBox[6].h = 60;

	textBox[7].x = 1000;
	textBox[7].y = 570;
	textBox[7].w = 100;
	textBox[7].h = 60;



	textSurface[0] = TTF_RenderText_Solid(font, "Music", black);
	textSurface[1] = TTF_RenderText_Solid(font, "Volume", black);
	textSurface[2] = TTF_RenderText_Solid(font, "SFX", black);
	textSurface[3] = TTF_RenderText_Solid(font, "SFX Volume", black);

	textSurface[4] = TTF_RenderText_Solid(font, "ON", white);
	textSurface[5] = TTF_RenderText_Solid(font, "100", white);
	textSurface[6] = TTF_RenderText_Solid(font, "ON", white);
	textSurface[7] = TTF_RenderText_Solid(font, "100", white);

	text[0] = SDL_CreateTextureFromSurface(r, textSurface[0]);
	text[1] = SDL_CreateTextureFromSurface(r, textSurface[1]);
	text[2] = SDL_CreateTextureFromSurface(r, textSurface[2]);
	text[3] = SDL_CreateTextureFromSurface(r, textSurface[3]);

	text[4] = SDL_CreateTextureFromSurface(r, textSurface[4]);
	text[5] = SDL_CreateTextureFromSurface(r, textSurface[5]);
	text[6] = SDL_CreateTextureFromSurface(r, textSurface[6]);
	text[7] = SDL_CreateTextureFromSurface(r, textSurface[7]);

}

void optionsScreen::Render(SDL_Renderer* r)
{
	for (int i = 0; i < 4; i++)
	{
		if (selectedItem == i)
		{
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
			SDL_RenderFillRect(r, &outline[selectedItem]);
			SDL_SetRenderDrawColor(r, 0, 0, 0, 120);
			SDL_RenderFillRect(r, &Optionsbuttons[i]);
		}

		else
		{
			SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
			SDL_RenderFillRect(r, &outline[i]);
			SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
			SDL_RenderFillRect(r, &Optionsbuttons[i]);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		SDL_RenderCopy(r, text[i], NULL, &textBox[i]);
	}
}

void optionsScreen::increaseSelectedItem()
{
	selectedItem++;

	if (selectedItem >= 4)
	{
		selectedItem = 3;
	}
}

void optionsScreen::decreaseSelectedItem()
{
	selectedItem--;
	if (selectedItem < 0)
	{
		selectedItem = 0;
	}
}