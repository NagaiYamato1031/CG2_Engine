#include "SceneManager.h"

#include <cassert>

void SceneManager::Initialize()
{
}

void SceneManager::Update()
{
	if (nextScene_)
	{
		delete currentScene_;
		currentScene_ = nextScene_;
		currentScene_->Initialize();
		nextScene_ = nullptr;
	}

	currentScene_->Update();
}

void SceneManager::Draw()
{
	currentScene_->Draw();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	nextScene_ = sceneFactory_->CreateScene(sceneName);
	nextScene_->SetSceneManager(this);
}
