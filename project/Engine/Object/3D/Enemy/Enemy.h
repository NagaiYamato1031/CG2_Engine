#pragma once

#include "../BaseCharacter.h"
#include "../../../Input/Input.h"
#include "../../../Shape/AABB.h"

class Enemy final : public BaseCharacter
{
/// <summary>
/// サブクラス
/// </summary>
private:

	enum PartsIndex {
		kEnemyBody,
		kEnemyHead,

		kEnemyCount,
	};


/// <summary>
/// プライベートメンバ変数
/// </summary>
private:

	const Vector3 kMovementRange = { 3.0f,0.0f,0.0f };
	const Vector3 kPopPosition = { 4.0f,0.0f,4.0f };

	AABB colliderAABB_;

	Vector3 velocity;

/// <summary>
/// オーバーライド
/// </summary>
public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw() override;

	void DebugGUI() override;

	void OnCollisionEnter() override;
	void OnCollision() override;
	void OnCollisionExit() override;

public:

	AABB* GetAABB(){ return &colliderAABB_; }

/// <summary>
/// プライベートメンバ関数
/// </summary>
private:

	void InitializeWorldTransforms();

	void UpdateMovement();

};