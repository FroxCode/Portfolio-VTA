#include "MapGeneration.h"

MapGeneration::MapGeneration(int width, int height, int columns, int rows) : m_w(width), m_h(height), m_cols(columns), m_rows(rows)
{
	srand(time(0));
	Initiliase();
}

MapGeneration::~MapGeneration()
{
}

void MapGeneration::Initiliase()
{
	rooms.clear();
	int size = m_w / m_cols;
	for (int i = 0; i < m_cols; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			rooms.push_back(new Rooms(i, j));

		}
	}
	rooms[15]->isBossRoom = true;
	room = rooms[0];
}

void MapGeneration::generate()
{
	while (roomStack.size() != 0 || !started)
	{
		started = true;
		room->isVisited = true;
		Rooms* nextRoom = GetRandomNeighbour(room);
		if (nextRoom != nullptr)
		{
			nextRoom->isVisited = true;
			roomStack.push(room);
			RemoveWalls(room, nextRoom);
			room = nextRoom;
			//roomStack.push(room);
		}
		else if (roomStack.size() > 0)
		{
			room = roomStack.top();
			roomStack.pop();
		}
	}
	//std::cout << roomStack.size() << std::endl;
	//std::cout << rooms.size() << std::endl;
}

void MapGeneration::RemoveWalls(Rooms * roomI, Rooms * roomJ)
{
	if (roomI->GetCol() == roomJ->GetCol() + 1)//right
	{
		roomI->leftWall = false;
		roomJ->rightWall = false;
	}
	else if (roomI->GetCol() == roomJ->GetCol() - 1)//left
	{
		roomI->rightWall = false;
		roomJ->leftWall = false;
	}
	else if (roomI->GetRow() == roomJ->GetRow() + 1)//top
	{
		roomI->topWall = false;
		roomJ->botWall = false;
	}
	else if (roomI->GetRow() == roomJ->GetRow() - 1)//bottom
	{
		roomI->botWall = false;
		roomJ->topWall = false;
	}
}

Rooms * MapGeneration::GetRandomNeighbour(Rooms * roomN)
{
	std::vector<Rooms*> availableNeighbours;
	int roomSize = rooms.size();
	//to check if it goes in different directions
	//Right
	int index = GetCellIndexPos(roomN->GetCol() + 1, roomN->GetRow());
	if (index < roomSize && index != -1)
	{
		if (!rooms[index]->isVisited)
		{
			availableNeighbours.push_back(rooms[index]);
		}
	}

	//Left
	index = GetCellIndexPos(roomN->GetCol() - 1, roomN->GetRow());
	if (index < roomSize && index != -1)
	{
		if (!rooms[index]->isVisited)
		{
			availableNeighbours.push_back(rooms[index]);
		}
	}

	//Top
	index = GetCellIndexPos(roomN->GetCol(), roomN->GetRow() - 1);
	if (index < roomSize && index != -1)
	{
		if (!rooms[index]->isVisited)
		{
			availableNeighbours.push_back(rooms[index]);
		}
	}

	//Bottom
	index = GetCellIndexPos(roomN->GetCol(), roomN->GetRow() + 1);
	if (index < roomSize && index != -1)
	{
		if (!rooms[index]->isVisited)
		{
			availableNeighbours.push_back(rooms[index]);
		}
	}

	if (availableNeighbours.size() > 0)
	{
		return availableNeighbours[(int)(rand() % availableNeighbours.size())];
	}
	else
	{
		return nullptr;
	}
}

int MapGeneration::GetCellIndexPos(int x, int y)
{
	if (x < 0 || y < 0 || x > m_cols - 1 || y > m_rows - 1)
	{
		return 0;
	}
	return ((y + 1) + ((x+1) * 4) - 4) -1;
}
Rooms* MapGeneration::getNextRoom(int dir)
{ //2 = N, 3 = E, 4 = S, 5 = W
	switch (dir)
	{
	case 2://n
		room = rooms.at(GetCellIndexPos(room->GetCol() , room->GetRow() - 1));
		break;
	case 3://e
		room = rooms.at(GetCellIndexPos(room->GetCol() + 1, room->GetRow() ));
		break;
	case 4://s
		room = rooms.at(GetCellIndexPos(room->GetCol(), room->GetRow() + 1));
		break;
	case 5://w
		room = rooms.at(GetCellIndexPos(room->GetCol()  -1, room->GetRow()));
		break;
	default:
		break;
	}
	return room;
}
Rooms* MapGeneration::getNextRoom() //just for first load
{
	return room;
}
