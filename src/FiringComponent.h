#pragma once
#include "Component.h"
#include "Gun.h"
#include <vector>
#include "SDL_mixer.h"


class FiringComponent : public Component
{
private:

	std::vector<Gun> guns;
	int m_currentGun;
	int m_timer;
	double m_fireRate = 1.0;
	bool readyToFire;
	int m_currentMagSize;
	bool canFire = true;
	Gun deagle;
	Gun ak;
	Gun shotgun;



public:
	FiringComponent() : Component("Firing") 
	{ 
		m_timer = 100; 
		readyToFire = false; 
		
		deagle.init(25, 7, 3, "deagle");
		ak.init(10, 30, 10, "ak");
		shotgun.init(50, 7, 1, "shotgun");

		guns.push_back(deagle);
		guns.push_back(ak);
		guns.push_back(shotgun);

		SFX_deagle = Mix_LoadWAV("assets/sfx/fire_deagle.wav");
		SFX_ak = Mix_LoadWAV("assets/sfx/fire_ak.wav");
		SFX_shotgun = Mix_LoadWAV("assets/sfx/fire_shotgun.wav");

		setCurrentGun("ak");
	}
	FiringComponent(std::string gunType) : Component("Firing")
	{
		m_timer = 100;
		readyToFire = false;

		deagle.init(25, 1, 0.75, "deagle");
		ak.init(10, 30, 10, "ak");
		shotgun.init(50, 7, 1, "shotgun");

		guns.push_back(deagle);
		guns.push_back(ak);
		guns.push_back(shotgun);

		SFX_deagle = Mix_LoadWAV("assets/sfx/fire_deagle.wav");
		SFX_ak = Mix_LoadWAV("assets/sfx/fire_ak.wav");
		SFX_shotgun = Mix_LoadWAV("assets/sfx/fire_shotgun.wav");

		setCurrentGun(gunType);

	}
	~FiringComponent() {};

	int getTimer() { return m_timer; }
	void setTimer(int t) { this->m_timer = t; }

	double getFireRate() { return guns.at(m_currentGun).getFireRate(); }
	int getMagSize() { return m_currentMagSize; }
	int getDamage() { return guns.at(m_currentGun).getDamage(); }
	int getCurrentGun() { return m_currentGun; }
	std::string getTag() { return guns.at(m_currentGun).getTag(); }

	bool getReady() { return readyToFire; }
	void setReady(bool rtf) { (this->readyToFire = rtf); }
	bool getCanFire() { return canFire; }
	void setCanFire(bool set) { canFire = set; }

	Mix_Chunk *SFX_deagle;
	Mix_Chunk *SFX_ak;
	Mix_Chunk *SFX_shotgun;
	//Change the current gun
	void setCurrentGun(std::string gunName)
	{
		for (int i = 0; i < guns.size(); i++)
		{
			if (guns.at(i).getTag() == gunName)
			{
				m_currentGun = i;
				m_currentMagSize = guns.at(i).getMag();
			}
		}
	}
	//Reduce the ammo count
	void updateCurrentMag()
	{
		m_currentMagSize--;
		if (m_currentMagSize <= 0)
		{
			if (guns.at(m_currentGun).getTag() != "deagle")
			{
				setCurrentGun("deagle");
			}
			else
			{
				m_currentMagSize = guns.at(m_currentGun).getMag();
			}
		}
	}
	bool fired = false;
};