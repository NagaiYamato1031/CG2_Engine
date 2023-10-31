#pragma once

#include "../../IObject.h"
#include "../../../Math/Math.h"

class FollowCamera {
public:
	void Initialize();

	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	ViewProjection* GetViewProjection() { return &viewProjection_; }

private:
	// カメラ
	ViewProjection viewProjection_;
	// 追従対象
	const WorldTransform* target_ = nullptr;
};