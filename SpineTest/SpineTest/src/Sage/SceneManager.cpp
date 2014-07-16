#include <Sage\sceneManager.h>
#include <Sage\IScene.h>

using namespace sage;

SceneManager::SceneManager()
{
	_currentScene = NULL;
}

void SceneManager::changeScene(const char* id)
{
	IScene *temp;
	std::vector<IScene*>::iterator itr;
	std::string tid;
	scenes->back()->deactivate();
	for (itr = scenes->begin(); itr < scenes->end(); itr++)
	{
		tid = (*itr)->getId();
		if (tid == id)
		{
			_currentScene = (*itr);
		}

	}
}

void SceneManager::AddScene(IScene* newScene)
{
	scenes->push_back(newScene);
}
IScene* SceneManager::getCurrentScene()
{
	return _currentScene;
}
void SceneManager::Terminate()
{
	std::vector<IScene*>::iterator iter;
	for (iter = scenes->begin(); iter != scenes->end(); iter++)
	{
		(*iter)->deactivate();
		delete *iter;
		*iter = NULL;
	}
	scenes->clear();
	delete scenes;

}

void SceneManager::Init()
{
	scenes = new std::vector<IScene*>;
	quit = false;
}
void setQuit(bool);