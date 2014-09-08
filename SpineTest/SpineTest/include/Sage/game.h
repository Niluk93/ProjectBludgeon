#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "sceneManager.h"
#include "ResourceManager.hpp"

class level_scene;
class menu_scene;

namespace sage
{

	class Game
	{
	public:
		const int VIDEO_WIDTH;
		const int VIDEO_HEIGHT;

		TextureManager textureManager;

		SceneManager sceneManager;
		bool mRunning;
		sf::VideoMode mode;
		sf::RenderWindow window;
		sf::Image icon;

		//Declare Scenes

		level_scene* demo;
		menu_scene*	menu;


		Game();
		void init();
		void run();
		void quit();
		void cleanup();

	};
}
