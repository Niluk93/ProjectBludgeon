#ifndef SPLASHSCENE_H
#define SPLASHSCENE_H

#include <stdio.h>

#include "IScene.h"
#include "sceneManager.h"


#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <Tmx\MapLoader.h>
#include <spine\spine-sfml.h>
#include "GESpineSprite.h"

using namespace std;
using namespace spine;


void callback(AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount) {
	TrackEntry* entry = AnimationState_getCurrent(state, trackIndex);
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;

	switch (type) {
	case ANIMATION_START:
		printf("%d start: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_END:
		printf("%d end: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_COMPLETE:
		printf("%d complete: %s, %d\n", trackIndex, animationName, loopCount);
		break;
	case ANIMATION_EVENT:
		printf("%d event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
			event->stringValue);
		break;
	}
	fflush(stdout);
}

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

level_scene::level_scene() :IScene("LEVEL_DEMO")
{
	mbLoadSuccess = true;
	iScrollFactor = 25.75f;


	//Load Maps
	mMapLoader = new tmx::MapLoader("data/Maps");
	if (mMapLoader)
	{
		mbLoadSuccess = true;
		mMapLoader->Load("level_test.tmx");
	}
		
	
}

void level_scene::onRegister()
{
	//Load Spine
	testSpineBoy = new GESpineSprite("data/spineboy", sf::Vector2f(300, 300), 0.0f, 1.0f);
	testSpineBoy->setAnimation("walk");
	//testSpineBoy->setSkin("goblin");
	//testSpineBoy->setAttachment("level_testleft hand item", "spear");
	testSpineBoy->setAnimationCallback(callback);


	//Viewport works
	mView = mGame->window.getView();
	mView.setCenter(sf::Vector2f(0, 0));
	//mView.zoom(2);
	mGame->window.setView(mView);
	//cout <<"X val :"<< mGame->window.getView().getCenter().x;
	//testSpineBoy->setPosition(mGame->window.getView().getCenter());
	testSpineBoy->setScale(0.1f, 0.1f);
}

void level_scene::update(float deltaTime)
{
	if (mbLoadSuccess)
	{
		mGame->window.draw(*mMapLoader);
		
		sf::IntRect viewRect = mGame->window.getViewport(mView);
		testSpineBoy->setPosition(0,-50);
		//testSpineBoy->setPosition(viewRect.left + viewRect.width * 0.5, viewRect.top + viewRect.height * -0.5);
		testSpineBoy->draw(&mGame->window, deltaTime);
	}

}

void level_scene::handleEvents(const sf::Event &evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
		if (evt.key.code == sf::Keyboard::Escape)
			mGame->quit();

		mView = mGame->window.getView();
		if (evt.key.code == sf::Keyboard::Down)
		{
			
			mView.move(sf::Vector2f(0.0f, iScrollFactor));
			mGame->window.setView(mView);
		}
		else if 
			(evt.key.code == sf::Keyboard::Up)
		{
			mView.move(sf::Vector2f(0.0f, iScrollFactor * -1));
			mGame->window.setView(mView);

		}
		else if
			(evt.key.code == sf::Keyboard::Right)
		{
			mView.move(sf::Vector2f(iScrollFactor, 0.0f));
			mGame->window.setView(mView);
		}
		else if
			(evt.key.code == sf::Keyboard::Left)
		{
			mView.move(sf::Vector2f(iScrollFactor * -1, 0.0f));
			mGame->window.setView(mView);
		}
		
	}
}

void level_scene::reactivate()
{
	
}

void level_scene::deactivate()
{

}

#endif