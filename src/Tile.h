//Created by Dale Sinnott, Connor Maguire
#ifndef _TILE_H_
#define _TILE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include "SDL_image.h"

class Tile {
public:

	Tile(SDL_Point position,
		SDL_Texture* _floorTexture,
		SDL_Texture* _wallTexture,
		SDL_Texture* _doorTexture,
		int const size);
	~Tile();

	void update();
	void render(SDL_Renderer *r);
	void updatePosition(SDL_Point newPos);
	
	SDL_Rect bounds;
	SDL_Texture* floorTexture;
	SDL_Texture* wallTexture;
	SDL_Texture* doorTexture;
	enum TileType 
	{ 
		FLOOR,
		WALL,
		DOOR_N,
		DOOR_E,
		DOOR_S,
		DOOR_W
	}; 

	void setType(Tile::TileType newType);
	TileType tileType;

};
#endif;
