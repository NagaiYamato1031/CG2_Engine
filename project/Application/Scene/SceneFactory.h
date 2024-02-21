#pragma once

#include "Scene/AbstractSceneFactory.h"

class SceneFactory : public AbstractSceneFactory
{
public:
	BaseScene* CreateScene(const std::string& sceneName) override;
};