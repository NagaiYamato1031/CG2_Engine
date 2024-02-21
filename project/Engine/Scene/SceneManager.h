#pragma once

#include "AbstractSceneFactory.h"
#include "Collider/CollisionManager.h"

class SceneManager final
{
private:
	AbstractSceneFactory* sceneFactory_ = nullptr;
	CollisionManager* collisionManager_ = nullptr;

	BaseScene* currentScene_ = nullptr;
	BaseScene* nextScene_ = nullptr;

private:
	const SceneManager& operator=(const SceneManager& obj) = delete;

public:
	SceneManager() {}

	void Initialize();

	void Update();

	void Draw();

	void SetSceneFactory(AbstractSceneFactory* factory) { sceneFactory_ = factory; }
	void SetCollisionManager(CollisionManager* collisionManager) { collisionManager_ = collisionManager; }

	CollisionManager* GetCollisionManager() { return collisionManager_; }
	void ChangeScene(const std::string& sceneName);
};