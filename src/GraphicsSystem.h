#pragma once
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "OnlineComponent.h"
#include "GraphicsComponent.h"
#include "Entity.h"
#include "SDL.h"
#include "SDL_image.h"
#include "ControlSystem.h"
#include "HUD.h"

class GraphicsSystem
{
	std::vector<Entity *> entities;
	SDL_Point pPos;
	SDL_Point bPos;
	std::shared_ptr<HUD> m_hud;
public:
	ControlSystem * controller;
	void addEntity(Entity &e) { entities.push_back(&e); }
	void update(SDL_Renderer* sdl_renderer, gameStates &states);
	void getHUD(std::shared_ptr<HUD> h) { m_hud = h; };
};