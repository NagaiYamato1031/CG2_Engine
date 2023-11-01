#pragma once

#include "../../IObject.h"
#include "../../../Shape/AABB.h"

class Floor final : public IObject
{
public:
	AABB aabb;

	bool isMove_ = false;

	Vector3 start_;
	Vector3 end_;

private:

	float moveT_ = 0.0f;

	float movingT_ = 0.01f;

public:

	void Initialize(Model* model, bool isMove = false);

	void Update() override;

	void Draw() override;

	void DebugGUI() override;

};