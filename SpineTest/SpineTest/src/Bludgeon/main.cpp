#include <Sage\game.h>

int main()
{

	sage::Game *Bludgeon = new sage::Game();
	Bludgeon->init();
	Bludgeon->run();
	Bludgeon->cleanup();

	return 0;

}