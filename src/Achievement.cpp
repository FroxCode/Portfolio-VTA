#include "Achievement.h"
int reviveTimer = 0;
int firstKillTimer = 0;
int newRoomTimer = 0;
int bossRoomTimer = 0;
int boostTimer = 0;
int newWeaponTimer = 0;
int noDropTimer = 0;
int velvetThunderTimer = 0;
int deadEndTimer = 0;
int levelUpTimer = 0;
Achievement::Achievement()
{

}

Achievement::~Achievement()
{
}

void Achievement::setName(std::string name,SDL_Renderer* renderer)
{
	this->achName = name;
	m_font = TTF_OpenFont("assets/Lazer84.ttf", 50);

	background.x = 300;
	background.y = 495;
	background.w = 650;
	background.h = 120;

	achRect.x = 325;
	achRect.y = 515;
	achRect.w = 600;
	achRect.h = 80;

	achSurface = TTF_RenderText_Solid(m_font, "Revive Me! - Revive your ally", SDL_Color{ 255,255,255 });
	achText[0] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "First blood - Kill your first enemy", SDL_Color{ 255,255,255 });
	achText[1] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "Behind door number.. - Go to a new room", SDL_Color{ 255,255,255 });
	achText[2] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "I'm the Captain now. - Kill the boss", SDL_Color{ 255,255,255 });
	achText[3] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "Pills here - Use a boost", SDL_Color{ 255,255,255 });
	achText[4] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "Oohh shiny - Pick up new weapon", SDL_Color{ 255,255,255 });
	achText[5] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "FML - Get no drop", SDL_Color{ 255,255,255 });
	achText[6] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "It's over 9000! - Use Velvet thunder", SDL_Color{ 255,255,255 });
	achText[7] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "Nothing to see here - Find a dead end", SDL_Color{ 255,255,255 });
	achText[8] = SDL_CreateTextureFromSurface(renderer, achSurface);

	achSurface = TTF_RenderText_Solid(m_font, "Level up - See before", SDL_Color{ 255,255,255 });
	achText[9] = SDL_CreateTextureFromSurface(renderer, achSurface);



	SDL_FreeSurface(achSurface);


}


void Achievement::Update(bool set,SDL_Renderer* renderer)
{
	if (set)
	{
		if (achName == "reviveMe")
		{
		if (firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
		{
			if (reviveTimer < 100 && reviveTimer >= 0)
			{
				reviveTimer++;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
				SDL_RenderFillRect(renderer, &background);
				SDL_RenderCopy(renderer, achText[0], nullptr, &achRect);
			}
			if (reviveTimer == 100)
			{
				reviveTimer = -1;
			}
		}
		}
		else if (achName == "firstKill")
		{
			if (reviveTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (firstKillTimer < 100 && firstKillTimer >= 0)
				{
					firstKillTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[1], nullptr, &achRect);
				}
				if (firstKillTimer == 100)
				{
					firstKillTimer = -1;
				}
			}
		}
		else if (achName == "newRoom")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (newRoomTimer < 100 && newRoomTimer >= 0)
				{
					newRoomTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[2], nullptr, &achRect);
				}
				if (newRoomTimer == 100)
				{
					newRoomTimer = -1;
				}
			}
		}
		else if (achName == "bossRoom")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (bossRoomTimer < 100 && bossRoomTimer >= 0)
				{
					bossRoomTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[3], nullptr, &achRect);
				}
				if (bossRoomTimer == 100)
				{
					bossRoomTimer = -1;
				}
			}
		}
		else if (achName == "useBoost")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (boostTimer < 100 && boostTimer >= 0)
				{
					boostTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[4], nullptr, &achRect);
				}
				if (boostTimer == 100)
				{
					boostTimer = -1;
				}
			}
		}
		else if(achName == "newWeapon")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (newWeaponTimer < 100 && newWeaponTimer >= 0)
				{
					newWeaponTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[5], nullptr, &achRect);
				}
				if (newWeaponTimer == 100)
				{
					newWeaponTimer = -1;
				}
			}
		}
		else if(achName == "noDrop")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (noDropTimer < 100 && noDropTimer >= 0)
				{
					noDropTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[6], nullptr, &achRect);
				}
				if (noDropTimer == 100)
				{
					noDropTimer = -1;
				}
			}
		}
		else if(achName == "velvetThunder")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && deadEndTimer < 1 && levelUpTimer < 1)
			{
				if (velvetThunderTimer < 100 && velvetThunderTimer >= 0)
				{
					velvetThunderTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[7], nullptr, &achRect);
				}
				if (velvetThunderTimer == 100)
				{
					velvetThunderTimer = -1;
				}
			}
		}
		else if(achName == "deadEnd")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && levelUpTimer < 1)
			{
				if (deadEndTimer < 100 && deadEndTimer >= 0)
				{
					deadEndTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[8], nullptr, &achRect);
				}
				if (deadEndTimer == 100)
				{
					deadEndTimer = -1;
				}
			}
		}
		else if (achName == "levelUp")
		{
			if (reviveTimer < 1 && firstKillTimer < 1 && newRoomTimer < 1 && bossRoomTimer < 1 && boostTimer < 1 && newWeaponTimer < 1 && noDropTimer < 1 && velvetThunderTimer < 1 && deadEndTimer < 1)
			{
				if (levelUpTimer < 100 && levelUpTimer >= 0)
				{
					levelUpTimer++;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
					SDL_RenderFillRect(renderer, &background);
					SDL_RenderCopy(renderer, achText[9], nullptr, &achRect);
				}
				if (levelUpTimer == 100)
				{
					levelUpTimer = -1;
				}
			}
		}
	}
}