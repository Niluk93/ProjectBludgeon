#pragma once
#include <Bludgeon\menu.h>

using namespace sage;

menu_scene::menu_scene() :IScene("MENU_DEMO")
{
	testTexture.loadFromFile("data/redball.png");
	testSprite.setTexture(testTexture);

}

void menu_scene::onRegister()
{
	


}

void menu_scene::update(float deltaTime)
{
	
	mGame->window.draw(testSprite);

}

void menu_scene::handleEvents(const sf::Event &evt)
{
	
}

void menu_scene::reactivate()
{

}

void menu_scene::deactivate()
{

}
