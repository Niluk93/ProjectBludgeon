#pragma once

#include <stdio.h>
#include <Sage\IScene.h>
#include <Sage\GESpineSprite.h>

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <Tmx\MapLoader.h>
#include <spine\spine-sfml.h>


using namespace std;
using namespace spine;
using namespace sage;


class level_scene : public IScene
{
public:
	level_scene();
	void update(float deltaTime);
	void handleEvents(const sf::Event &evt);
	void reactivate();
	void deactivate();
	void onRegister();

private:
	
	
	bool					mbLoadSuccess;
	int						iScrollFactor;
	tmx::MapLoader			*mMapLoader;
	sf::View				mView;
	GESpineSprite*			testSpineBoy;

	sf::Texture				testTexture;
	sf::Sprite				testSprite;

};