#pragma once

#include <memory>

class Input;
class TextureManager;
class CollisionManager;
class GlobalConfigs;
class SceneManager;

class BaseScene
{
protected:

	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	CollisionManager* collisionManager_ = nullptr;

	GlobalConfigs* configs_ = nullptr;

	SceneManager* sceneManager_ = nullptr;

public:
	virtual ~BaseScene() = default;

	void Init();
	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void SetSceneManager(SceneManager* manager);
};