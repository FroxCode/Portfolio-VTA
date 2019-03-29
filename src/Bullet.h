#pragma once
#include "SDL.h"
#include <string>
class Bullet
{
public:
	Bullet();
	~Bullet();

	Bullet(SDL_Renderer * r, const std::string & file, int lifeTime, SDL_Rect rect, float rot, float s, float d, std::string _shooterID);

	void render(SDL_Renderer * r);
	void update();

	bool isAlive;

	std::string getID();
	SDL_Rect getRect();

private:
	float xPos;
	float yPos;
	float m_speed;
	int m_ttl;
	int m_lifeSpan;
	void timeToLive();
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	float m_rotato;
	float m_dmg;
	std::string shooterID = "";
};

