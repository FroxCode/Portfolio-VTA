#include "Item.h"
#include <iostream>
Item::Item(SDL_Point _position, LootType _lootType, SDL_Renderer *r){
	bounds = { _position.x, _position.y, WIDTH, HEIGHT };
	originalY = _position.y;
	lootType = _lootType;
	switch (lootType)
	{
	case Item::AK:
		m_texture = IMG_LoadTexture(r, "assets/pickups/ak.png");
		break;
	case Item::SHOTGUN:
		m_texture = IMG_LoadTexture(r, "assets/pickups/shotgun.png");
		break;
	case Item::GREEN:
		m_texture = IMG_LoadTexture(r, "assets/pickups/green.png");
		break;
	case Item::YELLOW_SUNSHINE:
		m_texture = IMG_LoadTexture(r, "assets/pickups/yellowsunshine.png");
		break;
	case Item::GYM_CANDY:
		m_texture = IMG_LoadTexture(r, "assets/pickups/gymcandy.png");
		break;
	case Item::ELECTRIC_ICE:
		m_texture = IMG_LoadTexture(r, "assets/pickups/electricice.png");
		break;
	case Item::VELVET_THUNDER:
		m_texture = IMG_LoadTexture(r, "assets/pickups/velvetthunder.png");
		break;
	default:
		break;
	}
}
Item::~Item(){
}
void Item::render(SDL_Renderer *r){
	movingTimer++;
	if (movingTimer > 3)
	{
		movingTimer = 0;
		if (!switchDirection) {
			bounds.y--;
			if (bounds.y == originalY - 3) {
				switchDirection = !switchDirection;
			}
		}
		else {
			bounds.y++;
			if (bounds.y == originalY + 3) {
				switchDirection = !switchDirection;
			}
		}
	}
	
	SDL_RenderCopy(r, m_texture, NULL, &bounds);
}

