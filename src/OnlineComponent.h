#pragma once
#include "Component.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <sstream>

#include <vector>

#pragma comment(lib, "ws2_32.lib")

class OnlineComponent : public Component
{
public:
	OnlineComponent() : Component("Online") {}
	~OnlineComponent() {};
	std::string getIP(std::string c) { return ipAddress; }
	int getPort() { return port; }
	double getAngle()
	{
		return angle;
	}
	void setAngle(double a)
	{
		angle = a;
	}

private:
	std::string ipAddress = "149.153.106.164"; //change to host PC
	int port = 5050;
	double angle = 0;
	
};
