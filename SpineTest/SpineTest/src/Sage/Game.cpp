#pragma once
#include <SFML\System.hpp>
#include <Sage\game.h>
#include <Sage\IScene.h>


// Include the custom build scenes
#include <Bludgeon\menu.h>
#include <Bludgeon\Level.h>

using namespace sage;


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
	

	sceneManager.Init();
	//create scenes

	menu = new menu_scene();
	demo = new level_scene();
	
	

	sceneManager.AddScene(demo);
	sceneManager.AddScene(menu);
	sceneManager.changeScene("LEVEL_DEMO");

	std::vector<IScene*>::iterator itr;
	for (itr = sceneManager.scenes->begin(); itr < sceneManager.scenes->end(); itr++)
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
				sceneManager.getCurrentScene()->handleEvents(event);
		}

		window.clear();
		sceneManager.getCurrentScene()->update(currentFrame.asSeconds() - lastFrame.asSeconds());
		window.display();
		lastFrame = currentFrame;
		currentFrame = mainClock.getElapsedTime();
	}
}
void Game::cleanup()
{

	sceneManager.Terminate();
	window.close();

}


