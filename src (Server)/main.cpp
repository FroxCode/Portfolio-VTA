#include <iostream>
#include <string>
#include <assert.h>

#include "TcpListener.h"
#include "Qotd.h"
#include <vector>

using namespace std;

void initPlayers();

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock);
string PacketMaker(std::string id);
string SetupPacket(std::string id);

struct player
{
	int playerID = 0;
	int px = 0;
	int py = 0;
	int angle = 0;
	int fire = 0;
	int killCount = 0;
	int deaths = 0;
};

CTcpListener server("149.153.106.163", 5050, Listener_MessageReceived); //change this ip to server host ip

std::vector<player*> players;
int clients[4];

int systemID = 0;
int playersConnected = 0;
int myPlayerNumber = 0;
const int MAX_PLAYERS = 4;

void main()
{

	initPlayers();
	/*std::string tempIp;
	std::cout << "Enter IP Address: ";
	std::cin >> tempIp;
	int tempPort;
	std::cout << "Enter Port: ";
	std::cin >> tempPort;
	std::cout << "Your IP: " << tempIp << std::endl << "Your Port: " << tempPort << std::endl;*/
	//CTcpListener server("149.153.106.163", 5050, Listener_MessageReceived);
	
	if (server.Init())
	{
		while (1 != 0)
		{
			server.Run();
		}

	}
}

void initPlayers()
{
	for (int i = 0; i < 4; i++)
	{
		clients[i] = 0;
	}
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		players.push_back(new player());
	}
	
}

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock)
{
	std::string holder = "(NULL)";
	if (msg.find("(GIVEID)") != std::string::npos)
	{
		if (systemID == 0)
		{
			systemID = client;
			std::cout << "System ID" << client << std::endl;
		}
		else if (clients[0] == 0 && client != systemID)
		{
			clients[0] = client;
			myPlayerNumber = 1;
			playersConnected++;
			std::cout << "Player 1 connected: " << clients[0] << std::endl;
		}
		else if (clients[1] == 0 && client != systemID && client != clients[0])
		{
			clients[1] = client;
			myPlayerNumber = 2;
			playersConnected++;
			std::cout << "Player 2 connected: " << clients[1] << std::endl;
		}
		else if (clients[2] == 0 && client != systemID && client != clients[0] && client != clients[1])
		{
			clients[2] = client;
			myPlayerNumber = 3;
			playersConnected++;
			std::cout << "Player 3 connected: " << clients[2] << std::endl;
		}
		else if (clients[3] == 0 && client != systemID && client != clients[0] && client != clients[1] && client != clients[2])
		{
			clients[3] = client;
			myPlayerNumber = 4;
			playersConnected++;
			std::cout << "Player 4 connected: " << clients[3] << std::endl;
		}
		if (client != systemID)
		{
			holder = std::to_string(client);
		}
		listener->Send(client, SetupPacket(holder));
	}
	else
	{
		for (int i = 0; i < players.size(); i++)
		{
			std::cout << players.at(i) << std::endl;
		}

		if (client == clients[0])
		{
			std::cout << client << std::endl;
			std::cout << "Updating 1" << std::endl;
			std::cout << client << std::endl;
			players.at(0)->playerID = server._netOrder[1][0];
			players.at(0)->px = server._netOrder[1][1];
			players.at(0)->py = server._netOrder[1][2];
			players.at(0)->angle = server._netOrder[1][3];
			players.at(0)->fire = server._netOrder[1][4];
			players.at(0)->killCount = server._netOrder[1][5];
			players.at(0)->deaths = server._netOrder[1][6];
		}
		else if(client == clients[1])
		{
			std::cout << client << std::endl;
			std::cout << "Updating 2" << std::endl;		
			players.at(1)->playerID = server._netOrder[2][0];
			players.at(1)->px = server._netOrder[2][1];
			players.at(1)->py = server._netOrder[2][2];
			players.at(1)->angle = server._netOrder[2][3];
			players.at(1)->fire = server._netOrder[2][4];
			players.at(1)->killCount = server._netOrder[2][5];
			players.at(1)->deaths = server._netOrder[2][6];
		}
		else if (client == clients[2])
		{
			std::cout << client << std::endl;
			std::cout << "Updating 3" << std::endl;
			players.at(2)->playerID = server._netOrder[3][0];
			players.at(2)->px = server._netOrder[3][1];
			players.at(2)->py = server._netOrder[3][2];
			players.at(2)->angle = server._netOrder[3][3];
			players.at(2)->fire = server._netOrder[3][4];
			players.at(2)->killCount = server._netOrder[3][5];
			players.at(2)->deaths = server._netOrder[3][6];
		}
		else if (client == clients[3])
		{
			std::cout << client << std::endl;
			std::cout << "Updating 4" << std::endl;
			players.at(3)->playerID = server._netOrder[4][0];
			players.at(3)->px = server._netOrder[4][1];
			players.at(3)->py = server._netOrder[4][2];
			players.at(3)->angle = server._netOrder[4][3];
			players.at(3)->fire = server._netOrder[4][4];
			players.at(3)->killCount = server._netOrder[4][5];
			players.at(3)->deaths = server._netOrder[4][6];
		}
		listener->Send(client, PacketMaker(holder));
	}
	
}


string PacketMaker(std::string id)
{
	string holder;
	holder = id;
	holder += " ";

	//player values
	//for (int i = 0; i < players.size(); i++)
	//{
	//	
	//}
	holder += " ";
	holder += to_string(players.at(0)->playerID);
	holder += " ";
	holder += to_string(players.at(0)->px);
	holder += " ";
	holder += to_string(players.at(0)->py);
	holder += " ";
	holder += to_string(players.at(0)->angle);
	holder += " ";
	holder += to_string(players.at(0)->fire);
	holder += " ";
	holder += to_string(players.at(0)->killCount);
	holder += " ";
	holder += to_string(players.at(0)->deaths);


	holder += " ";
	holder += to_string(players.at(1)->playerID);
	holder += " ";
	holder += to_string(players.at(1)->px);
	holder += " ";
	holder += to_string(players.at(1)->py);
	holder += " ";
	holder += to_string(players.at(1)->angle);
	holder += " ";
	holder += to_string(players.at(1)->fire);
	holder += " ";
	holder += to_string(players.at(1)->killCount);
	holder += " ";
	holder += to_string(players.at(1)->deaths);

	holder += " ";
	holder += to_string(players.at(2)->playerID);
	holder += " ";
	holder += to_string(players.at(2)->px);
	holder += " ";
	holder += to_string(players.at(2)->py);
	holder += " ";
	holder += to_string(players.at(2)->angle);
	holder += " ";
	holder += to_string(players.at(2)->fire);
	holder += " ";
	holder += to_string(players.at(2)->killCount);
	holder += " ";
	holder += to_string(players.at(2)->deaths);

	holder += " ";
	holder += to_string(players.at(3)->playerID);
	holder += " ";
	holder += to_string(players.at(3)->px);
	holder += " ";
	holder += to_string(players.at(3)->py);
	holder += " ";
	holder += to_string(players.at(3)->angle);
	holder += " ";
	holder += to_string(players.at(3)->fire);
	holder += " ";
	holder += to_string(players.at(3)->killCount);
	holder += " ";
	holder += to_string(players.at(3)->deaths);

	return holder;
}
string SetupPacket(std::string id)
{
	string holder;
	holder = id;
	holder += " ";
	holder += to_string(myPlayerNumber);
	holder += " ";
	holder += to_string(playersConnected);

	return holder;
}