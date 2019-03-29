#include "Game.h"


/**Create and initialises an instance of game, and clean up when the game is closed*/

int main(int argc, char* argv[])
{
	Game game;

	if (!game.init()) {
		std::cout << "Failed to init game" << '\n';
	}

	//run the game loop
	game.loop();

	game.destroy();

	return 0;
}
