#include "levelLoader.h"

LevelLoader::LevelLoader() {}
LevelLoader::~LevelLoader() {}


void LevelLoader::load(std::string textFile)
{
	//Resets the array
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			level[i][j] = 0;
		}
	}
	//Open file and input into the array 
	std::ifstream file;
	file.open(textFile);
	if (file.is_open())
	{
		std::cout << "File Opened" << std::endl;
		while (!file.eof())
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					file >> level[i][j];
				}
			}
		}
	}
	file.close();
}

void LevelLoader::loadRoom(Rooms* newRoom)
{
	std::cout << newRoom->GetRow() << ", " << newRoom->GetCol() << std::endl;

	//Resets the array
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			level[i][j] = 0;
		}
	}

	//insert wall around level
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
			{
				level[i][j] = 1; //insert wall at edges
			}
			
		}
	}

	//remove walls and place doors
	if (!newRoom->topWall)
	{
		level[0][WIDTH / 2] = 2; //north wall
		std::cout << "top" << std::endl;
	}
	if (!newRoom->rightWall)
	{
		level[6][WIDTH - 1] = 3; //east wall
		std::cout << "right" << std::endl;
	}
	if (!newRoom->botWall)
	{
		level[HEIGHT - 1][WIDTH / 2] = 4; //south wall
		std::cout << "bottom" << std::endl;
	}
	if (!newRoom->leftWall)
	{
		level[6][0] = 5; //west wall
		std::cout << "left" << std::endl;
	}
}