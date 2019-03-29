#pragma once
#include "Rooms.h"
#include <stdio.h>
#include <vector>
#include <stack>
#include <SDL.h>
#include <time.h>
#include <iostream>

class MapGeneration
{
private:

	int m_w;
	int m_h;
	int m_rows;
	int m_cols;

	SDL_Renderer *m_r;
	std::vector<Rooms*> rooms;
	std::stack<Rooms*> roomStack;

	bool started = false;

public:
	MapGeneration(int width, int height, int columns, int rows);
	~MapGeneration();
	Rooms* room;
	bool bossRoom = false;
	void Initiliase();
	void generate();
	void RemoveWalls(Rooms* roomI, Rooms* roomJ);
	Rooms* getNextRoom(int dir);
	Rooms* getNextRoom();
	Rooms* GetRandomNeighbour(Rooms* roomN);
	int GetCellIndexPos(int x, int y);

};