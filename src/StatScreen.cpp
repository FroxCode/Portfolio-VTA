#include "StatScreen.h"


statScreen::statScreen()
{
}

statScreen::~statScreen()
{
}

void statScreen::intialise(SDL_Renderer* r)
{
	font = TTF_OpenFont("assets/VCR.ttf", 50);




	background.x = 15;
	background.y = 320;
	background.w = 200;
	background.h = 290;

	textBox[0].x = 20;
	textBox[0].y = 330;
	textBox[0].w = 55;
	textBox[0].h = 55;

	textBox[1].x = 20;
	textBox[1].y = 400;
	textBox[1].w = 55;
	textBox[1].h = 55;

	textBox[2].x = 20;
	textBox[2].y = 470;
	textBox[2].w = 55;
	textBox[2].h = 55;

	textBox[3].x = 20;
	textBox[3].y = 540;
	textBox[3].w = 55;
	textBox[3].h = 55;

	textBox[4].x = 140;
	textBox[4].y = 330;
	textBox[4].w = 55;
	textBox[4].h = 55;

	textBox[5].x = 140;
	textBox[5].y = 400;
	textBox[5].w = 55;
	textBox[5].h = 55;

	textBox[6].x = 140;
	textBox[6].y = 470;
	textBox[6].w = 55;
	textBox[6].h = 55;

	textBox[7].x = 140;
	textBox[7].y = 540;
	textBox[7].w = 55;
	textBox[7].h = 55;

	textSurface[0] = TTF_RenderText_Solid(font, "HP:", white);
	textSurface[1] = TTF_RenderText_Solid(font, "ATT:", white);
	textSurface[2] = TTF_RenderText_Solid(font, "DEF:", white);
	textSurface[3] = TTF_RenderText_Solid(font, "AGI:", white);
	textSurface[4] = TTF_RenderText_Solid(font, "100", white);
	textSurface[5] = TTF_RenderText_Solid(font, "100", white);
	textSurface[6] = TTF_RenderText_Solid(font, "100", white);
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



void statScreen::Render(SDL_Renderer* r)
{
	if (display)
	{
		SDL_SetRenderDrawColor(r, 0, 0, 0, 125);
		SDL_RenderFillRect(r, &background);

		for (int i = 0; i < 8; i++)
		{
			SDL_RenderCopy(r, text[i], NULL, &textBox[i]);
		}
	}
}

void statScreen::setDisplay()
{
	if (display)
	{
		display = false;
	}

	else if (!display)
	{
		display = true; 
	}
}

void statScreen::updateStats(SDL_Renderer* r,int hp, float att, float agi, float def)
{
	std::string s;	
	s = std::to_string(hp);
	textSurface[4] = TTF_RenderText_Solid(font, s.c_str() , white);
	s = convToString(att);
	textSurface[5] = TTF_RenderText_Solid(font, s.c_str(), white);
	s = convToString(def);
	textSurface[6] = TTF_RenderText_Solid(font, s.c_str(), white);
	s = convToString(agi);
	textSurface[7] = TTF_RenderText_Solid(font, s.c_str(), white);

	text[4] = SDL_CreateTextureFromSurface(r, textSurface[4]);
	text[5] = SDL_CreateTextureFromSurface(r, textSurface[5]);
	text[6] = SDL_CreateTextureFromSurface(r, textSurface[6]);
	text[7] = SDL_CreateTextureFromSurface(r, textSurface[7]);
}
std::string statScreen::convToString(float val)
{
	int num = val;
	int decimal = (val * 10) - (num * 10);
	return (std::to_string(num) + ". " + std::to_string(decimal));
}