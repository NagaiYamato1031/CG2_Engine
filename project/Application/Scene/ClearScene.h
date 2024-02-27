#pragma once

#include "Adapter/Adapter.h"
#include "Scene/BaseScene.h"

class ClearScene : public BaseScene
{
private:


	std::unique_ptr<Sprite> spriteClear_;
	std::unique_ptr<Sprite> spriteSpace_;

public:

	void Initialize() override;

	void Update() override;

	void Draw() override;
};