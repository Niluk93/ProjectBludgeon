#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>

class level_scene;

class Game
{
public:
	const int VIDEO_WIDTH;
	const int VIDEO_HEIGHT;
	bool mRunning;
	sf::VideoMode mode;
	sf::RenderWindow window;
	sf::Image icon;
	
	//Declare Scenes
	level_scene* demo;
	

	Game();
	void init();
	void run();
	void quit();
	void cleanup();
	
	

};

#endif