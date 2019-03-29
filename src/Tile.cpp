//Created by Dale Sinnott, Connor Maguire
#include "Tile.h"
#include <iostream>
Tile::Tile(SDL_Point position, SDL_Texture* _floorTexture,
	SDL_Texture* _wallTexture, SDL_Texture* _doorTexture, int const size = 64)
{
	floorTexture = _floorTexture;
	wallTexture = _wallTexture;
	doorTexture = _doorTexture;

	bounds.y = position.y;
	bounds.x = position.x;
	bounds.w = size; 
	bounds.h = size;

	tileType = Tile::FLOOR;
}
Tile::~Tile()
{

}
void Tile::update()
{
	
}
void Tile::setType(Tile::TileType newType)
{
	tileType = newType;
}
void Tile::render(SDL_Renderer *r)
{
	switch (tileType)
	{
	case Tile::FLOOR:
		SDL_RenderCopy(r, floorTexture, NULL, &bounds);
		break;
	case Tile::WALL:
		SDL_RenderCopy(r, wallTexture, NULL, &bounds);
		break;
	case Tile::DOOR_N:
		SDL_RenderCopy(r, doorTexture, NULL, &bounds);
		break;
	case Tile::DOOR_E:
		SDL_RenderCopy(r, doorTexture, NULL, &bounds);
		break;
	case Tile::DOOR_S:
		SDL_RenderCopy(r, doorTexture, NULL, &bounds);
		break;
	case Tile::DOOR_W:
		SDL_RenderCopy(r, doorTexture, NULL, &bounds);
		break;
	default:
		break;
	}
}
void Tile::updatePosition(SDL_Point newPos)
{
	bounds.y = newPos.y;
	bounds.x = newPos.x;
}