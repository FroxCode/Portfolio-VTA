//Created by Dale Sinnott
#ifndef _ITEM_H_
#define _ITEM_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include "SDL_image.h"

class Item {
public:
	enum LootType //lootTable
	{
		AK,
		SHOTGUN,
		GREEN,
		YELLOW_SUNSHINE,
		GYM_CANDY,
		ELECTRIC_ICE,
		VELVET_THUNDER
	};

	Item(SDL_Point _position, LootType _lootType, SDL_Renderer *r);
	~Item();

	void render(SDL_Renderer *r);

	SDL_Rect bounds;
	SDL_Texture* m_texture;

	void setLootType(LootType newType) { lootType = newType; }
	LootType getLootType() { return lootType; }

private:
	LootType lootType;
	int move_limiter = 3; //pixels to move
	int originalY;
	int movingTimer = 0;
	bool switchDirection = false;
	int const WIDTH = 32;
	int const HEIGHT = 32;
};
#endif;
