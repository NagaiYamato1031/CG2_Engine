#pragma once

#include "../Math/Math.h"
#include "../Object/WorldTransform.h"

class AABB
{
public:
	WorldTransform transform_;

	Vector3 min_ = { -1.0f,-1.0f,-1.0f };
	Vector3 max_ = { 1.0f,1.0f,1.0f };
	Vector3 center_{ 0.0f,0.0f,0.0f };

	AABB GetAABB() {
		AABB aabb = *this;
		Vector3 position = transform_.GetWorldPos();
		Vector3 scale = transform_.GetScale();
		aabb.min_ = { this->min_.x * scale.x,this->min_.y * scale.y,this->min_.z * scale.z };
		aabb.min_ = aabb.min_ + position;
		aabb.max_ = { this->max_.x * scale.x,this->max_.y * scale.y,this->max_.z * scale.z };
		aabb.max_ = aabb.max_ + position;
		return aabb;
	}

	bool IsCollision(AABB* a) {
		AABB aabb1 = this->GetAABB();
		AABB aabb2 = a->GetAABB();

		if ((aabb1.min_.x <= aabb2.max_.x && aabb1.max_.x >= aabb2.min_.x) && // x 軸
			(aabb1.min_.y <= aabb2.max_.y && aabb1.max_.y >= aabb2.min_.y) && // y 軸
			(aabb1.min_.z <= aabb2.max_.z && aabb1.max_.z >= aabb2.min_.z) // z 軸
			) {
			return true;
		}
		return false;
	}
	AABB* IsCollision(AABB** a, size_t size = 1) {
		AABB aabb1 = GetAABB();
		for (size_t i = 0; i < size; i++)
		{
			AABB aabb2 = a[i]->GetAABB();

			if ((aabb1.min_.x <= aabb2.max_.x && aabb1.max_.x >= aabb2.min_.x) && // x 軸
				(aabb1.min_.y <= aabb2.max_.y && aabb1.max_.y >= aabb2.min_.y) && // y 軸
				(aabb1.min_.z <= aabb2.max_.z && aabb1.max_.z >= aabb2.min_.z) // z 軸
				) {
				return a[i];
			}
		}
		return nullptr;
	}
};