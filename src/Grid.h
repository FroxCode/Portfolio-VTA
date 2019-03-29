////////////////////////////////////////////////////////////
//
// Created by Dale Sinnott, Connor Maguire
//
////////////////////////////////////////////////////////////
#ifndef _Grid_H_
#define _Grid_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <vector>
#include "LevelLoader.h"
#include "Tile.h"
#include "Rooms.h"

class Grid 
{
public:
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Grid(int _w, int _h);


	////////////////////////////////////////////////////////////
	/// Updates the object
	///
	////////////////////////////////////////////////////////////
	void initialise(int level, SDL_Renderer *r);
	void initialise(Rooms* newRoom, SDL_Renderer *r);

	////////////////////////////////////////////////////////////
	/// Updates the object
	///
	////////////////////////////////////////////////////////////
	void update();

	////////////////////////////////////////////////////////////
	/// Drwas the object and it's components
	///
	////////////////////////////////////////////////////////////
	void render(SDL_Renderer *r);
	std::string floorTexturePath = "assets/floor.png";
	std::string wallTexturePath = "assets/wall.png";
	std::string doorTexturePath = "assets/door.png";
	
	std::vector<std::shared_ptr<Tile>> map;
	int w;
	int h;
private:
	LevelLoader lLoader;

};
#endif;