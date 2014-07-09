#ifndef GAME_H
#include"game.h"
#endif

#ifndef ISCENE_H
#define ISCENE_H
#include<iostream>
#include<SFML\System.hpp>
class IScene
{
public:
	
	bool mPaused;
	std::string ID;
	
	IScene(std::string sceneId):
	  mGame(NULL),
	  mPaused(true),
	  ID(sceneId)
	  {
	  }
	  virtual ~IScene()
	  {
		  
	  }
	void registerGame(Game *g)
	{
		mGame = g;
		onRegister();
	}
	virtual void onRegister();
	virtual void pause();
	virtual void update(float deltaTime) = 0;
	virtual void handleEvents(const sf::Event &evt) = 0;
	virtual void reactivate() = 0;
	virtual void deactivate() = 0;
	std::string getId();


	Game *mGame;

};

std::string IScene::getId()
{
	return ID;
}

void IScene::pause()
{
	mPaused = true;
}

void IScene::onRegister()
{

}

#endif