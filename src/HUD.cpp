#include "HUD.h"



HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::initialise(SDL_Renderer* r, SDL_Point cam)
{
	boostColour = { 255, 255, 255, 255 };
	colour = { 255, 255, 255 };

	bossRed = 255;
	theBossIsHere = false;
	m_font = TTF_OpenFont("assets/Lazer84.ttf", 300);
	m_sdl_renderer = r;
	
	//Health texture
	healthSurface = TTF_RenderText_Solid(m_font, "Health", colour);
	healthText = SDL_CreateTextureFromSurface(r, healthSurface);
	SDL_FreeSurface(healthSurface);

	//Healthbar back rect
	m_healthBarB = { 65 + cam.x , 20 + cam.y, 250, 35 };

	//Healthbar rect
	m_healthBar = { 180 + cam.x , 25 + cam.y, 130, 25 };

	//Healthbar text rect
	m_healthBarT = { 70 + cam.x , 20 + cam.y, 100, 32 };

	m_allyHealthBarB = {500,500,55,11};
	m_allyHealthBar = { 502,503,50,5 };

	//EXP texture
	expSurface = TTF_RenderText_Solid(m_font, "EXP", colour);
	expText = SDL_CreateTextureFromSurface(r, expSurface);
	SDL_FreeSurface(expSurface);

	//EXP back rect
	m_expBarB = { 945 + cam.x , 20 + cam.y, 270, 35 };

	//EXP rect
	m_expBar = { 1065 + cam.x , 25 + cam.y, 1, 25 };

	//EXP text rect
	m_expBarT = { 950 + cam.x , 20 + cam.y, 100, 32 };

	//Level
	colour = { 255, 0, 255 };
	lvlSurface = TTF_RenderText_Solid(m_font, "Lvl: 0", colour);
	lvlText = SDL_CreateTextureFromSurface(r, lvlSurface);
	SDL_FreeSurface(lvlSurface);

	m_lvlBar = { 1105 + cam.x , 25 + cam.y, 60, 25 };

	//Gun stuff
	akText = IMG_LoadTexture(r, "assets/ak.png");
	pistolText = IMG_LoadTexture(r, "assets/pistol.png");
	shotgunText = IMG_LoadTexture(r, "assets/shotgun.png");
	guns.push_back(pistolText);
	guns.push_back(akText);
	guns.push_back(shotgunText);

	m_gunRect = { 1021 + cam.x , 640 + cam.y, 100, 64 };
	m_gunBkg = { 1016 + cam.x , 640 + cam.y, 200, 64 };
	
	colour = { 255, 255, 255 };
	ammoSurface = TTF_RenderText_Solid(m_font, "~", colour);
	ammoText[0] = SDL_CreateTextureFromSurface(r, ammoSurface);
	for (int i = 1; i < 31; i++)
	{
		ammoSurface = TTF_RenderText_Solid(m_font, std::to_string(i).c_str(), colour);
		ammoText[i] = SDL_CreateTextureFromSurface(r, ammoSurface);
	}
	SDL_FreeSurface(ammoSurface);
	
	m_ammoRect = {1121 + cam.x, 640 + cam.y, 90, 64};

	//Boost 

	greenIcon = IMG_LoadTexture(r, "assets/green.png");
	yellowSunshineIcon = IMG_LoadTexture(r, "assets/yellowSunshine.png");
	gymCandyIcon = IMG_LoadTexture(r, "assets/gymCandy.png");
	electicIceIcon = IMG_LoadTexture(r, "assets/electricIce.png");
	velvetThunderIcon = IMG_LoadTexture(r, "assets/velvetThunder.png");
	boosts.push_back(greenIcon);
	boosts.push_back(yellowSunshineIcon);
	boosts.push_back(gymCandyIcon);
	boosts.push_back(electicIceIcon);
	boosts.push_back(velvetThunderIcon);


	m_boostBackg = { 65 + cam.x , 640 + cam.y, 200, 64 };
	m_boostLabel = { 75 + cam.x, 640 + cam.y, 100, 64 };
	m_boostSquare = {190 + cam.x, 640 + cam.y, 64, 64 };
	m_boostBar = { 254 + cam.x, 640 + cam.y, 500, 64 };

	boostSurface = TTF_RenderText_Solid(m_font, "Boost:", colour);
	boostText = SDL_CreateTextureFromSurface(r, boostSurface);
	SDL_FreeSurface(boostSurface);
	if (currentGun == 0)
	{
		currentAmmoText = ammoText[0];
	}
	else if (currentGun == 1)
	{
		currentAmmoText = ammoText[30];
	}
	else if (currentGun == 2)
	{
		currentAmmoText = ammoText[7];
	}

	//Boss
	colour = { 255, 255, 255 };
	bossSurface = TTF_RenderText_Solid(m_font, "BOSS", colour);
	bossText = SDL_CreateTextureFromSurface(r, bossSurface);
	SDL_FreeSurface(bossSurface);

	m_bossHealthBarB = {400 + cam.x, 60 + cam.y, 410, 64};
	m_bossHealthBar = { 405 + cam.x, 65 + cam.y, 400, 44 };
	m_bossHealthBarT = {520 + cam.x, 0 + cam.y, 160, 64};
}
void HUD::render(SDL_Renderer* r)
{
	

	//Black backg
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderFillRect(r, &m_healthBarB);
	SDL_RenderFillRect(r, &m_expBarB);
	SDL_RenderFillRect(r, &m_allyHealthBarB);

	if (theBossIsHere)
	{
		//Boss health bar + text
		SDL_RenderFillRect(r, &m_bossHealthBarB);
		SDL_SetRenderDrawColor(r, bossRed, 0, 0, 255);
		SDL_RenderFillRect(r, &m_bossHealthBar);
		SDL_RenderCopy(r, bossText, nullptr, &m_bossHealthBarT);
	}
	
	//Healthbar
	SDL_RenderCopy(r, healthText, nullptr, &m_healthBarT);
	SDL_SetRenderDrawColor(r, red, 0, green, 255);
	SDL_RenderFillRect(r, &m_healthBar);

	SDL_SetRenderDrawColor(r, redA, 0, greenA, 255);
	SDL_RenderFillRect(r, &m_allyHealthBar);


	//EXP bar
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderCopy(r, expText, nullptr, &m_expBarT);
	SDL_RenderFillRect(r, &m_expBar);

	//Level
	SDL_RenderCopy(r, lvlText, nullptr, &m_lvlBar);

	//Guns
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderFillRect(r, &m_gunBkg);
	SDL_RenderCopy(r, currentAmmoText, nullptr, &m_ammoRect);
	SDL_RenderCopy(r, guns.at(currentGun), NULL, &m_gunRect);
	//Boosts
	if (boostTimer > 0)
	{
		SDL_SetRenderDrawColor(r, boostColour.r, boostColour.g, boostColour.b, boostColour.a);
		SDL_RenderFillRect(r, &m_boostBar);
	}
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderFillRect(r, &m_boostBackg);
	SDL_RenderCopy(r, boostText, nullptr, &m_boostLabel);
	if (currentBoost > 0)
	{
		SDL_RenderCopy(r, boosts.at(currentBoost-1), NULL, &m_boostSquare);
	}
	
}
void HUD::updateBoostColour(SDL_Color c)
{
	boostColour = c;
}
void HUD::updateBoostBar()
{
	m_boostBar.w = 500 * (boostTimer / 200.0f);
}
void HUD::updateHealthbar(double currentHp, double maxHP)
{
	double hpc = currentHp / maxHP;
	m_healthBar.w = maxHPWidth * hpc;
	int currentColour = 255 * hpc;
	red = 255 - currentColour;
	green = 0 + currentColour;

}
void HUD::updateBossHp(double currentHp, double maxHP)
{
	double hpc = currentHp / maxHP;
	m_bossHealthBar.w = maxBossHpWidth * hpc;
	// = 255 * hpc;

}

void HUD::updateExperienceBar(double cEXP, double maxExp)
{
	if (cEXP > maxExp)
	{
		double remainder = cEXP - maxExp;
		m_expBar.w = (remainder / maxExp) * 100;
	}
	else
	{
		double expP = cEXP / maxExp;
		m_expBar.w = maxEXPWidth * expP;
	}
	

}

void HUD::updateLevel(int lvl)
{
	colour = { 255, 0, 255 };
	std::string t = "Lvl: " + std::to_string(lvl);
	const char* c = t.c_str();

	lvlSurface = TTF_RenderText_Solid(m_font, c, colour);
	lvlText = SDL_CreateTextureFromSurface(m_sdl_renderer, lvlSurface);
	SDL_FreeSurface(lvlSurface);

}

void HUD::updateBullets(int currentBullets, int cGun)
{
	currentGun = cGun;
	
	std::string t;
	if (currentGun != 0)
	{
		currentAmmoText = ammoText[currentBullets];
	}
	else
	{
		currentAmmoText = ammoText[0];
	}
	colour = { 255, 255, 255 };
}

void HUD::updateBoost(int b)
{
	currentBoost = b;
}
void HUD::updateBoostTimer()
{
	if (boostTimer > 0)
	{
		boostTimer--;
	}
}
void HUD::reset(SDL_Point cam)
{
	//Healthbar back rect
	m_healthBarB.x = 15 + cam.x;
	m_healthBarB.y = 20 + cam.y;
	m_healthBarB.w = 250;
	m_healthBarB.h = 35;

	//Healthbar rect
	m_healthBar.x = 130 + cam.x;
	m_healthBar.y = 25 + cam.y;
	m_healthBar.w = 130;
	m_healthBar.h = 25;

	//Healthbar text rect
	m_healthBarT.x = 20 + cam.x;
	m_healthBarT.y = 20 + cam.y;
	m_healthBarT.w = 100;
	m_healthBarT.h = 32;

	//EXP back rect
	m_expBarB.x = 15 + cam.x;
	m_expBarB.y = 20 + cam.y;
	m_expBarB.w = 250;
	m_expBarB.h = 35;

	//EXP rect
	m_expBar.x = 130 + cam.x;
	m_expBar.y = 25 + cam.y;
	m_expBar.w = 130;
	m_expBar.h = 25;

	//EXP text rect
	m_expBarT.x = 20 + cam.x;
	m_expBarT.y = 20 + cam.y;
	m_expBarT.w = 100;
	m_expBarT.h = 32;
}

void HUD::updateHealthbarPosition(int x, int y)
{
	m_allyHealthBarB.x = x;
	m_allyHealthBar.x = x + 2;
	
	m_allyHealthBarB.y = y;
	m_allyHealthBar.y = y + 3;
}

void HUD::updateAllyHealthBar(double currentHp, double maxHP)
{
	double hpc = currentHp / maxHP;
	m_allyHealthBar.w = maxAllyHPWidth * hpc;
	int currentColour = 255 * hpc;
	redA = 255 - currentColour;
	greenA = 0 + currentColour;

}