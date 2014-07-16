#pragma once

#include <stdio.h>
#include <Sage\IScene.h>

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>


using namespace sage;




class menu_scene : public IScene
{
public:
	menu_scene();
	void update(float deltaTime);
	void handleEvents(const sf::Event &evt);
	void reactivate();
	void deactivate();
	void onRegister();

private:


	sf::Texture				testTexture;
	sf::Sprite				testSprite;

};