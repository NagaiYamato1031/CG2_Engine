#include "BaseScene.h"

#include "Adapter/Adapter.h"

void BaseScene::Init()
{
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	collisionManager_ = std::make_unique<CollisionManager>();

	configs_ = GlobalConfigs::GetInstance();
}

void BaseScene::SetSceneManager(SceneManager* manager)
{
	sceneManager_ = manager;
}
