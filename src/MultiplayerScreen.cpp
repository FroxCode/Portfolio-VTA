#include "MultiplayerScreen.h"

#include <iostream>

multiplayerScreen::multiplayerScreen()
{
}

multiplayerScreen::~multiplayerScreen()
{
}

void multiplayerScreen::intialise(SDL_Renderer* r)
{
	font = TTF_OpenFont("assets/VCR.ttf", 50);

	SDL_Color black = { 0,0,0 };
	SDL_Color white = { 255,255,255 };
	SDL_Color playerColour = { 255, 0, 0 };

	outline[0].x = 550;
	outline[0].y = 560;
	outline[0].w = 200;
	outline[0].h = 100;

	buttons[0].x = 560;
	buttons[0].y = 570;
	buttons[0].w = 180;
	buttons[0].h = 80;


	textBox[0].x = 600;
	textBox[0].y = 580;
	textBox[0].w = 100;
	textBox[0].h = 60;

	textBox[1].x = 550;
	textBox[1].y = 20;
	textBox[1].w = 200;
	textBox[1].h = 120;

	textBox[2].x = 290;
	textBox[2].y = 200;
	textBox[2].w = 100;
	textBox[2].h = 60;

	textBox[3].x = 890;
	textBox[3].y = 200;
	textBox[3].w = 100;
	textBox[3].h = 60;

	textBox[4].x = 290;
	textBox[4].y = 400;
	textBox[4].w = 100;
	textBox[4].h = 60;

	textBox[5].x = 890;
	textBox[5].y = 400;
	textBox[5].w = 100;
	textBox[5].h = 60;

	textBox[6].x = 0;
	textBox[6].y = 0;
	textBox[6].w = 0;
	textBox[6].h = 0;

	textSurface[0] = TTF_RenderText_Solid(font, "Start", black);
	textSurface[1] = TTF_RenderText_Solid(font, "Lobby", white);
	//Players
	textSurface[2] = TTF_RenderText_Solid(font, "Player 1", playerColour);
	playerColour = { 0, 255, 0 };
	textSurface[3] = TTF_RenderText_Solid(font, "Player 2", playerColour);
	playerColour = { 255, 0, 255 };
	textSurface[4] = TTF_RenderText_Solid(font, "Player 3", playerColour);
	playerColour = { 255,255,0 };
	textSurface[5] = TTF_RenderText_Solid(font, "Player 4", playerColour);
	//you txt
	textSurface[6] = TTF_RenderText_Solid(font, "(You)", white);

	text[0] = SDL_CreateTextureFromSurface(r, textSurface[0]);
	text[1] = SDL_CreateTextureFromSurface(r, textSurface[1]);
	text[2] = SDL_CreateTextureFromSurface(r, textSurface[2]);
	text[3] = SDL_CreateTextureFromSurface(r, textSurface[3]);
	text[4] = SDL_CreateTextureFromSurface(r, textSurface[4]);
	text[5] = SDL_CreateTextureFromSurface(r, textSurface[5]);
	text[6] = SDL_CreateTextureFromSurface(r, textSurface[6]);
}

void multiplayerScreen::Render(SDL_Renderer* r)
{


	SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	SDL_RenderFillRect(r, &outline[selectedItem]);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 120);
	SDL_RenderFillRect(r, &buttons[0]);


	SDL_RenderCopy(r, text[0], NULL, &textBox[0]);
	SDL_RenderCopy(r, text[1], NULL, &textBox[1]);
	SDL_RenderCopy(r, text[6], NULL, &textBox[6]);

	switch (playerCount)
	{
	case 1:
		SDL_RenderCopy(r, text[2], NULL, &textBox[2]);
		break;
	case 2:
		SDL_RenderCopy(r, text[2], NULL, &textBox[2]);
		SDL_RenderCopy(r, text[3], NULL, &textBox[3]);
		break;
	case 3:
		SDL_RenderCopy(r, text[2], NULL, &textBox[2]);
		SDL_RenderCopy(r, text[3], NULL, &textBox[3]);
		SDL_RenderCopy(r, text[4], NULL, &textBox[4]);
		break;
	case 4:
		SDL_RenderCopy(r, text[2], NULL, &textBox[2]);
		SDL_RenderCopy(r, text[3], NULL, &textBox[3]);
		SDL_RenderCopy(r, text[4], NULL, &textBox[4]);
		SDL_RenderCopy(r, text[5], NULL, &textBox[5]);
		break;
	default:
		break;
	}
}

void multiplayerScreen::increaseSelectedItem()
{
	selectedItem++;

	if (selectedItem >= 2)
	{
		selectedItem = 1;
	}
}

void multiplayerScreen::decreaseSelectedItem()
{
	selectedItem--;
	if (selectedItem < 0)
	{
		selectedItem = 0;
	}
}
void multiplayerScreen::setPlayerCount(int pc)
{
	playerCount = pc;
}
void multiplayerScreen::setMyNumber(int num)
{
	if (myNumber == 0)
	{
		switch (num)
		{
		case 1:
			textBox[6].x = 400;
			textBox[6].y = 200;
			textBox[6].w = 100;
			textBox[6].h = 60;
			break;
		case 2:
			textBox[6].x = 1000;
			textBox[6].y = 200;
			textBox[6].w = 100;
			textBox[6].h = 60;
			break;
		case 3:
			textBox[6].x = 400;
			textBox[6].y = 400;
			textBox[6].w = 100;
			textBox[6].h = 60;
			break;
		case 4:
			textBox[6].x = 1000;
			textBox[6].y = 400;
			textBox[6].w = 100;
			textBox[6].h = 60;
			break;
		default:
			break;
		}
		myNumber = num;
	}
	
}