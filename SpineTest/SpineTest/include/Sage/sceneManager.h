#pragma once

//#include "IScene.h"
#include <vector>



namespace sage
{
	class IScene;
	class SceneManager
	{
	public:
		std::vector<IScene*> *scenes;

		bool quit;

		SceneManager();

		void changeScene(const char* id);

		void AddScene(IScene* newScene);

		IScene* getCurrentScene();

		void Terminate();

		void Init();

		void setQuit(bool val){ quit = val; }

	private:

		IScene* _currentScene;

	};

}


