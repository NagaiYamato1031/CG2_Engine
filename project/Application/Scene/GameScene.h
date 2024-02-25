#pragma once

#include "Adapter/Adapter.h"
#include "Scene/BaseScene.h"

class GameScene : public BaseScene
{
private:

	std::unique_ptr<ViewProjection> view_;

public:

	void Initialize() override;

	void Update() override;

	void Draw() override;
};