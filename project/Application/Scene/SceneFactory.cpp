#include "SceneFactory.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
	BaseScene* newScene = nullptr;

	if (sceneName == "TITLE")
	{
		newScene = new TitleScene;
	}
	else if (sceneName == "GAMEPLAY")
	{
		newScene = new GameScene;
	}
	else if (sceneName == "CLEAR")
	{
		newScene = new ClearScene;
	}

	return newScene;
}
