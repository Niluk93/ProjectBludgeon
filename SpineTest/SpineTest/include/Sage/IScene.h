#pragma once


#include<iostream>
#include<SFML\System.hpp>
#include "game.h"


namespace sage
{

	class IScene
	{

	public:

		std::string ID;
		Game *mGame;

		IScene(std::string sceneId) :
			mGame(NULL),
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


		virtual void update(float deltaTime) = 0;
		virtual void handleEvents(const sf::Event &evt) = 0;
		virtual void onRegister() = 0;
		virtual void reactivate() = 0;
		virtual void deactivate() = 0;
		std::string getId()
		{
			return ID;
		}

	};
}




