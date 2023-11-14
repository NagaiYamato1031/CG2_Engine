#pragma once

#include "../Math/Math.h"

class Collider
{
private:

	float colliderRadius_ = 1.0f;

public:

	virtual ~Collider() = default;

	virtual void OnCollisionEnter();
	virtual void OnCollision() {}
	virtual void OnCollisionExit();

	virtual Vector3 GetCenterPosition() = 0;

	float GetRadius()const { return colliderRadius_; }
	void SetRadius(float radius) { colliderRadius_ = radius; }

};