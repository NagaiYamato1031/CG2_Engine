#include "BaseScene.h"

#include "Adapter/Adapter.h"

void BaseScene::Init()
{
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	configs_ = GlobalConfigs::GetInstance();
}

void BaseScene::SetSceneManager(SceneManager* manager)
{
	sceneManager_ = manager;
	collisionManager_ = sceneManager_->GetCollisionManager();
}
