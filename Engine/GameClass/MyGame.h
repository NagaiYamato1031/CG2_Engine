#pragma once

#include "Framework.h"

class MyGame : public Framework
{
public:

	~MyGame() override;

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<Sprite> spriteUV_;
	std::unique_ptr<Sprite> spriteWHITE_;

};