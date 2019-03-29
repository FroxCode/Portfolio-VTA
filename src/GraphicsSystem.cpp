 #include "GraphicsSystem.h"

void GraphicsSystem::update(SDL_Renderer* sdl_renderer, gameStates &states ) {
	if (states.currentState == gameStates::GAME)
	{
		for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++) {
			SDL_Rect *sr = new SDL_Rect;

			for (int j = 0; j < (*i)->getComponents().size(); j++) {
				if ((*i)->getComponents().at(j)->getID() == "Position") {
					if ((*i)->getTag() == "Boss")
					{
						sr->h = 128;
						sr->w = 128;
						sr->x = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().x + 64;
						sr->y = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().y + 64;
						std::string iTag = (*i)->getTag();
					}
					else
					{
						sr->h = 64;
						sr->w = 64;
						sr->x = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().x + 16;
						sr->y = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().y + 16;
						std::string iTag = (*i)->getTag();
					}
				}
			}
			for (int k = 0; k < (*i)->getComponents().size(); k++) {
				if ((*i)->getComponents().at(k)->getID() == "Graphics") {
					if ((*i)->getTag() == "Player")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++)
						{
							if ((*i)->getComponents().at(l)->getID() == "Control") {
								SDL_RenderCopyEx(sdl_renderer, static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getTexture(), nullptr, sr,
									static_cast<ControlComponent*>((*i)->getComponents().at(l))->getAngle(), (0, 0), SDL_FLIP_NONE);
							}

						}
					}
					else if ((*i)->getTag() == "Boss")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++) {
							if ((*i)->getComponents().at(l)->getID() == "Health") {
								if (static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth() >= 600)
								{
									static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->setTexture(IMG_LoadTexture(sdl_renderer, "assets/boss_p1.png"));
								}
								else if (static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth() >= 300)
								{
									static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->setTexture(IMG_LoadTexture(sdl_renderer, "assets/boss_p2.png"));
								}
								else
								{
									static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->setTexture(IMG_LoadTexture(sdl_renderer, "assets/boss_p3.png"));
								}
								SDL_RenderCopyEx(sdl_renderer, static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getTexture(), nullptr, sr,
									static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getAngle(), (0, 0), SDL_FLIP_NONE);
							}
						}
					}
					else if ((*i)->getTag() != "OnlinePlayer")
					{
						SDL_RenderCopyEx(sdl_renderer, static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getTexture(), nullptr, sr,
							static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getAngle(), (0, 0), SDL_FLIP_NONE);
					}
				}

			}

			for (int l = 0; l < (*i)->getComponents().size(); l++)
			{
				if ((*i)->getComponents().at(l)->getID() == "Health")
				{
					if ((*i)->getTag() == "Player")
					{
						m_hud->updateHealthbar(static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth(), static_cast<HealthComponent*>((*i)->getComponents().at(l))->getMaxHealth());
					}
					if ((*i)->getTag() == "Ally")
					{
						m_hud->updateAllyHealthBar(static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth(), static_cast<HealthComponent*>((*i)->getComponents().at(l))->getMaxHealth());
					}
					if ((*i)->getTag() == "Boss")
					{
						m_hud->updateBossHp(static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth(), static_cast<HealthComponent*>((*i)->getComponents().at(l))->getMaxHealth());
					}
				}
			}
		}
		m_hud->render(sdl_renderer);
	}
	else if (states.mpState == gameStates::MP_PLAYING)
	{
		for (std::vector<Entity*>::iterator i = entities.begin(), e = entities.end(); i != e; i++) {
			SDL_Rect *sr = new SDL_Rect;

			for (int j = 0; j < (*i)->getComponents().size(); j++) {
				if ((*i)->getComponents().at(j)->getID() == "Position") {
					sr->h = 32;
					sr->w = 32;
					sr->x = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().x + 16;
					sr->y = static_cast<PositionComponent*>((*i)->getComponents().at(j))->getPosition().y + 16;
					std::string iTag = (*i)->getTag();
				}
			}
			for (int k = 0; k < (*i)->getComponents().size(); k++) {
				if ((*i)->getComponents().at(k)->getID() == "Graphics") {
					if ((*i)->getTag() == "Player")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++)
						{
							if ((*i)->getComponents().at(l)->getID() == "Control") {
								SDL_RenderCopyEx(sdl_renderer, static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getTexture(), nullptr, sr,
									static_cast<ControlComponent*>((*i)->getComponents().at(l))->getAngle(), (0, 0), SDL_FLIP_NONE);
							}
						}
					}
					else if ((*i)->getTag() == "OnlinePlayer")
					{
						for (int l = 0; l < (*i)->getComponents().size(); l++)
						{
							if ((*i)->getComponents().at(l)->getID() == "Online") {
								SDL_RenderCopyEx(sdl_renderer, static_cast<GraphicsComponent*>((*i)->getComponents().at(k))->getTexture(), nullptr, sr,
									static_cast<OnlineComponent*>((*i)->getComponents().at(l))->getAngle(), (0, 0), SDL_FLIP_NONE);
							}
						}
					}
				}
			}

			for (int l = 0; l < (*i)->getComponents().size(); l++)
			{
				if ((*i)->getComponents().at(l)->getID() == "Health")
				{
					if ((*i)->getTag() == "Player")
					{
						m_hud->updateHealthbar(static_cast<HealthComponent*>((*i)->getComponents().at(l))->getHealth(), static_cast<HealthComponent*>((*i)->getComponents().at(l))->getMaxHealth());
					}
				}
			}
		}
	}
}