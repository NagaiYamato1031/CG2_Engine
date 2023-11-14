#pragma once

#include <list>

#include "Collider.h"

class CollisionManager final
{
private:

	std::list<Collider*> colliders_;

public:

	void Reset();

	void AddObject(Collider* collider);

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	void CheckCollisionAll();
};