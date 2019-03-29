//Created by Dale Sinnott
#include "Grid.h"
#include <iostream>
Grid::Grid(int _w = 20, int _h = 11)
{
	w = _w;
	h = _h;
}
void Grid::update()
{
	for (int i = 0; i < h * w; i++)
	{
		map.at(i)->update();
	
	}
}
void Grid::render(SDL_Renderer *r)
{
	for (int i = 0; i < h * w; i++)
	{
		map.at(i)->render(r);
	}
}
void Grid::initialise(int level, SDL_Renderer *r)
{
	//Load the level grid from a text file
	switch (level)
	{
	case 1:
		lLoader.load("data/level1.txt");
		break;
	default:
		std::cout << "error loading level" << std::endl;
		break;
	}

	SDL_Texture* floorTexture = IMG_LoadTexture(r, floorTexturePath.c_str());
	SDL_Texture* wallTexture = IMG_LoadTexture(r, wallTexturePath.c_str());
	SDL_Texture* doorTexture = IMG_LoadTexture(r, doorTexturePath.c_str());

	SDL_Point defaultPos = { 0 * 64, 0 * 64 };

	Tile tempTile(defaultPos, floorTexture, wallTexture, doorTexture, 64);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{//set tiles into grid
			SDL_Point tPos = { x * 64, y * 64 };
			tempTile.updatePosition(tPos);
			switch (lLoader.level[y][x])
			{
			case 1:
				tempTile.setType(Tile::WALL);
				break;
			default:
				tempTile.setType(Tile::FLOOR);
				break;
			}
			map.push_back(std::make_shared<Tile>(tempTile));
		}
	}
}
void Grid::initialise(Rooms* newRoom, SDL_Renderer *r)
{
	map.clear();
	lLoader.loadRoom(newRoom);

	SDL_Texture* floorTexture = IMG_LoadTexture(r, floorTexturePath.c_str());
	SDL_Texture* wallTexture = IMG_LoadTexture(r, wallTexturePath.c_str());
	SDL_Texture* doorTexture = IMG_LoadTexture(r, doorTexturePath.c_str());

	SDL_Point defaultPos = { 0 * 64, 0 * 64 };

	Tile tempTile(defaultPos, floorTexture, wallTexture, doorTexture, 64);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{//set tiles into grid
			SDL_Point tPos = { x * 64, y * 64 };
			tempTile.updatePosition(tPos);
			switch (lLoader.level[y][x])
			{
			case 1:
				tempTile.setType(Tile::WALL);
				break;
			case 2:
				tempTile.setType(Tile::DOOR_N);
				break;
			case 3:
				tempTile.setType(Tile::DOOR_E);
				break;
			case 4:
				tempTile.setType(Tile::DOOR_S);
				break;
			case 5:
				tempTile.setType(Tile::DOOR_W);
				break;
			default:
				tempTile.setType(Tile::FLOOR);
				break;
			}
			map.push_back(std::make_shared<Tile>(tempTile));
		}
	}
}