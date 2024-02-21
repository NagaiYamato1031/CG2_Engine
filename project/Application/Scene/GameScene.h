#pragma once

#include "Adapter/Adapter.h"
#include "Scene/BaseScene.h"

class GameScene : public BaseScene
{
private:


public:

	void Initialize() override;

	void Update() override;

	void Draw() override;
};