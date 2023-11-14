#pragma once

#include "../../IObject.h"
#include "../../../Math/Math.h"

class FollowCamera {
public:
	void Initialize();

	void Update();

	void SetTarget(WorldTransform* target) { target_ = target; Reset(); }

	ViewProjection* GetViewProjection() { return &viewProjection_; }

	void Reset();

	Vector3 CalcOffset() const;

	void DebugGUI();

private:
	// カメラ
	ViewProjection viewProjection_;
	// 追従対象
	WorldTransform* target_ = nullptr;

	Vector3 interTarget_;

	float destinationAngleY_ = 0.0f;

	float cLerpRate_ = 0.3f;
};