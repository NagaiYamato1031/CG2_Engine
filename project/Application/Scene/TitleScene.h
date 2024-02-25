#pragma once

#include "Adapter/Adapter.h"
#include "Scene/BaseScene.h"

class TitleScene : public BaseScene
{
private:


	std::unique_ptr<Sprite> spriteUV_;
	std::unique_ptr<Sprite> spriteWHITE_;

public:

	void Initialize() override;

	void Update() override;

	void Draw() override;
};