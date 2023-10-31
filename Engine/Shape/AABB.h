#pragma once

#include "../Math/Math.h"
#include "../Object/3D/WorldTransform.h"

class AABB
{
public:
	WorldTransform transform_;

	Vector2 min_ = { -1.0f,-1.0f };
	Vector2 max_ = { 1.0f,1.0f };
	Vector2 center_{ 0.0f,0.0f };
};