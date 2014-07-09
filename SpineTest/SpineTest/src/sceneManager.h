#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include "IScene.h"
#include <vector>

class IScene;
class SceneManager
{
public :
	std::vector<IScene*> *scenes;
	bool quit;

	static SceneManager* GetInstance();
	void changeScene(const char*);
	void AddScene(IScene*);
	IScene* getCurrentScene();
	void Terminate();
	void Init();
	void setQuit(bool);
	
private:


	static SceneManager* _instance;
	IScene* _currentScene;
	SceneManager();


};



SceneManager* SceneManager::_instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if(_instance == NULL)
	{
		_instance = new SceneManager();
		

	}
	return _instance;
}

void SceneManager::AddScene(IScene* newScene)
{
	scenes->push_back(newScene);
	
}

void SceneManager::changeScene(const char* id)
{
	IScene *temp;
	std::vector<IScene*>::iterator itr;
	std::string tid;
	scenes->back()->deactivate();
	for(itr = scenes->begin(); itr < scenes->end(); itr++)
	{
		tid = (*itr)->getId();
		if(tid == id)
		{
			_currentScene = (*itr);
		}

	}
}

IScene* SceneManager::getCurrentScene()
{
	return _currentScene;
}

void SceneManager::Terminate()
{
	std::vector<IScene*>::iterator iter;
	for(iter = scenes->begin(); iter != scenes->end(); iter++)
	{
		(*iter)->deactivate();
		delete *iter;
		*iter = NULL;
	}
	scenes->clear();
	delete scenes;

	if(_instance)
		delete _instance;
	_instance = NULL;
}

SceneManager::SceneManager()
{
	_currentScene = NULL;
}

void SceneManager::Init()
{
	scenes = new std::vector<IScene*>;
	quit = false;
}

#endif