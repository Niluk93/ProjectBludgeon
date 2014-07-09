#include <SFML\System.hpp>

#include "game.h"
#include "IScene.h"
#include "sceneManager.h"

// Include the custom build scenes
#include "Level.h"


Game::Game():
VIDEO_WIDTH(800),
	VIDEO_HEIGHT(600),
	mRunning(true)
{

}
void Game::init()
{

	mode.height = VIDEO_HEIGHT;
	mode.width = VIDEO_WIDTH;
	window.create(mode,"Tmx Level Loader",sf::Style::Close);

	window.setVerticalSyncEnabled(true);
	//window.setIcon(60,60,icon.getPixelsPtr());
	//window.setFramerateLimit(60);

	SceneManager::GetInstance()->Init();
	//create scenes

	demo = new level_scene();
	

	SceneManager::GetInstance()->AddScene(demo);
	
	SceneManager::GetInstance()->changeScene("LEVEL_DEMO");

	std::vector<IScene*>::iterator itr;
	for(itr = SceneManager::GetInstance()->scenes->begin(); itr < SceneManager::GetInstance()->scenes->end(); itr++)
		(*itr)->registerGame(this);





}
void Game::quit()
{
	mRunning = false;
}
void Game::run()
{
	sf::Clock mainClock;
	mainClock.restart();
	sf::Time lastFrame, currentFrame;
	currentFrame = mainClock.getElapsedTime();
	while (window.isOpen() && mRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				quit();
			else
				SceneManager::GetInstance()->getCurrentScene()->handleEvents(event);
		}

		window.clear();
		SceneManager::GetInstance()->getCurrentScene()->update(currentFrame.asSeconds() - lastFrame.asSeconds());
		window.display();
		lastFrame = currentFrame;
		currentFrame = mainClock.getElapsedTime();
	}
}
void Game::cleanup()
{

	SceneManager::GetInstance()->Terminate();
	window.close();

}


