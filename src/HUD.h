#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <vector>

class HUD
{
public:
	HUD();
	~HUD();

	void render(SDL_Renderer * r);

	void initialise(SDL_Renderer * r, SDL_Point cam);
	void reset(SDL_Point cam);

	//Healthbar
	void updateHealthbar(double currentHp, double maxHP);

	//AllyHealthBar
	void updateAllyHealthBar(double currentHp, double maxHp);

	void updateHealthbarPosition(int x, int y);

	//Experience bar
	void updateExperienceBar(double cEXP, double maxExp);

	//level
	void updateLevel(int lvl);

	//Boost
	void updateBoost(int b);

	//Update bullets
	void updateBullets(int currentBullets, int cGun);

	void updateBossHp(double currentHp, double maxHp);

	bool isAlive;
	bool theBossIsHere;
	void updateBoostTimer();
	void setBoostTimer() { boostTimer = 200; }
	int getBoostTimer() { return boostTimer; }
	void updateBoostBar();
	void updateBoostColour(SDL_Color c);
	


private:
	//Keeps track of the current gun equiped for drawing gun icon
	//Colour
	SDL_Color colour;
	//Colour
	SDL_Color boostColour;
	

	//positions of the 
	SDL_Rect m_healthBarT;
	SDL_Rect m_healthBarB;
	SDL_Rect m_healthBar;
	SDL_Rect m_expBar;
	SDL_Rect m_expBarB;
	SDL_Rect m_expBarT;
	SDL_Rect m_lvlBar;
	SDL_Rect m_boostSquare;
	SDL_Rect m_boostBackg;
	SDL_Rect m_boostLabel;
	SDL_Rect m_boostBarT;
	SDL_Rect m_boostBar;
	SDL_Rect m_allyHealthBarB;
	SDL_Rect m_allyHealthBar;

	SDL_Rect m_bossHealthBarB;
	SDL_Rect m_bossHealthBar;
	SDL_Rect m_bossHealthBarT;

	//bullet rects
	SDL_Rect m_ammoRect;
	SDL_Rect m_gunRect;
	SDL_Rect m_gunBkg;
	
	//icons
	std::vector<SDL_Texture*> guns;
	std::vector<SDL_Texture*> boosts;

	//font
	TTF_Font* m_font;

	//text surfaces
	SDL_Surface* healthSurface;
	SDL_Texture* healthText;

	SDL_Surface* expSurface;
	SDL_Texture* expText;

	SDL_Surface* lvlSurface;
	SDL_Texture* lvlText;

	SDL_Surface* bossSurface;
	SDL_Texture* bossText;

	//Guns
	SDL_Texture* akText;
	SDL_Texture* pistolText;
	SDL_Texture* shotgunText;

	SDL_Surface* ammoSurface;
	SDL_Texture* ammoText[31];
	SDL_Texture* currentAmmoText;

	SDL_Surface* boostSurface;
	SDL_Texture* boostText;
	SDL_Texture* greenIcon;
	SDL_Texture* yellowSunshineIcon;
	SDL_Texture* gymCandyIcon;
	SDL_Texture* electicIceIcon;
	SDL_Texture* velvetThunderIcon;

	SDL_Renderer* m_sdl_renderer;

	//Scalars
	int maxEXPWidth = 145;
	int maxHPWidth = 130;
	int maxAllyHPWidth = 50;
	int maxBossHpWidth = 400;
	int red;
	int green;
	int redA;
	int greenA;
	int bossRed;

	//Identifiers:
	//0 - pistol
	//1 - Ak
	//2 - shotgun
	int currentGun = 2;

	//0 - no boost
	//1 - green
	//2 - yellow sunshine
	//3 - gym candy
	//4 - electric ice
	//5 - velvet thunder
	int currentBoost = 0;
	int boostTimer = 0;
};

