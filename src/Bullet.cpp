#include "Bullet.h"
#include "SDL_image.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{

}

Bullet::Bullet(SDL_Renderer * r, const std::string & file, int lifeTime, SDL_Rect rect, float rot, float s, float d, std::string _shooterID) :
	xPos(rect.x), yPos(rect.y), m_rect(rect) , m_lifeSpan(lifeTime), m_rotato(rot), m_speed(s), m_dmg(d), shooterID(_shooterID)
{
	isAlive = true;
	m_ttl = 0;
	m_texture = IMG_LoadTexture(r, file.c_str());
}

void Bullet::update()
{
	xPos += cos(m_rotato * 3.14159265 / 180) * m_speed;
	yPos += sin(m_rotato * 3.14159265 / 180) * m_speed;
	timeToLive();
}

void Bullet::render(SDL_Renderer * r)
{
	m_rect.x = xPos;
	m_rect.y = yPos;
	SDL_RenderCopyEx(r, m_texture, nullptr, &m_rect,
		m_rotato, (0, 0), SDL_FLIP_NONE);
}

void Bullet::timeToLive()
{
	m_ttl++;
	if (m_lifeSpan < m_ttl)
	{
		isAlive = false;
	}
}
std::string Bullet::getID()
{
	return shooterID;
}
SDL_Rect Bullet::getRect()
{
	return m_rect;
}