#include "CollisionManager.h"

#include <cassert>

void CollisionManager::Reset()
{
	colliders_.clear();
}

void CollisionManager::AddObject(Collider* collider)
{
	assert(collider);
	colliders_.push_back(collider);
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB)
{
	Vector3 centerA = colliderA->GetCenterPosition();
	Vector3 centerB = colliderB->GetCenterPosition();

	Vector3 subtract = centerB - centerA;

	float distance = Vector3::Length(subtract);

	if (distance < colliderA->GetRadius() + colliderB->GetRadius()) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}

}

void CollisionManager::CheckCollisionAll()
{
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			CheckCollisionPair(colliderA, colliderB);

		}
	}
}
