#pragma once
#include <stdio.h>
#include <SDL.h>

class Rooms
{
private:
	int m_row, m_col;
	int	m_wallWidth = 1;

public:
	Rooms(int col, int row);
	~Rooms() {};

	bool isVisited = false;
	bool rightWall = true;
	bool leftWall = true;
	bool topWall = true;
	bool botWall = true;
	bool isBossRoom = false;
	int GetCol()
	{
		return m_col;
	}

	int GetRow()
	{
		return m_row;
	}
};