#include "SceneManager.h"

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}

void SceneManager::Initialze()
{
	scenes_[Scene::TITLE].reset(new TitleScene);
	scenes_[Scene::GAME].reset(new GameScene);

	for (size_t i = 0; i < Scene::_COUNT; i++)
	{
		scenes_[i]->Initialize();
	}
}

void SceneManager::Reset()
{
	for (size_t i = 0; i < Scene::_COUNT; i++)
	{
		scenes_[i]->Reset();
	}
}

void SceneManager::Update()
{
	CheckChangeScene();

	scenes_[currentIndex_]->Update();
}

void SceneManager::DrawModel()
{
	scenes_[currentIndex_]->DrawModel();
}

void SceneManager::DrawSprite()
{
	scenes_[currentIndex_]->DrawSprite();
}

void SceneManager::Debug()
{
#ifdef _DEBUG



	scenes_[currentIndex_]->Debug();

#endif // _DEBUG
}

void SceneManager::CheckChangeScene()
{
	if (currentIndex_ != scenes_[currentIndex_]->GetSceneNo())
	{
		currentIndex_ = scenes_[currentIndex_]->GetSceneNo();
		scenes_[currentIndex_]->Reset();
	}
}
