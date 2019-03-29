#pragma once
#include "Component.h"

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(std::string& id, SDL_Renderer* renderer) : Component("Graphics")
	{
		m_texture = IMG_LoadTexture(renderer, id.c_str());
		sdl_renderer = renderer;
	}
	~GraphicsComponent() {};
	SDL_Texture* getTexture(){ return m_texture; }
	void setTexture(SDL_Texture* newTexture) { (this->m_texture = newTexture); }
	float getAngle() { return angle; }
	SDL_Point getCurrentFrame() { return currentFrame; }
	void setCurrentFrame(SDL_Point frame) { currentFrame = frame; }
	SDL_Rect getRect() { return frameRect; }
	void setCurrentRect(SDL_Rect rect) { frameRect = rect; }
	void setAngle(float newAngle) 
	{ 
		(this->angle = newAngle);
	}
	SDL_Renderer* sdl_renderer;
private:
	SDL_Texture* m_texture;
	float angle;
	SDL_Point currentFrame = { 0, 0 };
	SDL_Rect frameRect = { 0, 0, 64, 64 };
};

