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
	ViewProjection* vp = nullptr;

	static const uint32_t kNumIndex_ = 10;

	std::unique_ptr<Particle> particle_;
	WorldTransform wt[kNumIndex_];
};