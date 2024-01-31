#pragma once

#include <array>
#include <memory>

#include "IScene.h"
#include "SceneList.h"

class SceneManager final
{
private:

	std::array<std::unique_ptr<IScene>, Scene::_COUNT> scenes_;

	Scene currentIndex_ = Scene::TITLE;

public:

	static SceneManager* GetInstance();

	void Initialze();
	void Reset();

	void Update();

	void DrawModel();
	void DrawSprite();

	void Debug();

private:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager& obj) = delete;
	const SceneManager& operator=(const SceneManager& obj) = delete;
private:

	void CheckChangeScene();

};