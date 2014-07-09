#include "game.h"

int main()
{

	Game *Bludgeon = new Game();
	Bludgeon->init();
	Bludgeon->run();
	Bludgeon->cleanup();

	return 0;

}