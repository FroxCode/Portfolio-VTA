#pragma once
#include <iostream>
#include <string>
class Gun
{
public:
	Gun() {};
	~Gun() {};

	void init(int dmg, int mag, double fireRate, std::string tag)
	{
		m_dmg = dmg;
		m_mag = mag;
		m_fireRate = fireRate;
		m_tag = tag;
	}
		
	int getDamage() { return m_dmg; }
	int getMag() { return m_mag; }
	double getFireRate() { return m_fireRate; }
	std::string getTag() { return m_tag; }

private:

	int m_dmg;
	int m_mag;
	double m_fireRate;
	std::string m_tag;
};

