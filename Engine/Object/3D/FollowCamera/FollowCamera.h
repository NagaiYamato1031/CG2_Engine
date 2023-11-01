#pragma once

#include "../../IObject.h"
#include "../../../Math/Math.h"

class FollowCamera {
public:
	void Initialize();

	void Update();

	void SetTarget(WorldTransform* target) { target_ = target; }

	ViewProjection* GetViewProjection() { return &viewProjection_; }

private:
	// カメラ
	ViewProjection viewProjection_;
	// 追従対象
	WorldTransform* target_ = nullptr;
};