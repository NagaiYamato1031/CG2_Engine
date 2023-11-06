#include "Enemy.h"

#include <numbers>
#include <cmath>

void Enemy::Initialize(const std::vector<Model*>& models)
{
	models_ = models;
	transformBase_.Initialize();
	transforms_.clear();
	InitializeWorldTransforms();
	colliderAABB_.transform_.Initialize();
	colliderAABB_.transform_.SetParent(&transformBase_);
	colliderAABB_.min_ = { -0.5f,0.0f,-0.5f };
	colliderAABB_.max_ = { 0.5f,0.7f,0.5f };
	velocity = { 0.1f,0.0f,0.0f, };
}

void Enemy::Update()
{
	DebugGUI();

	UpdateMovement();

	UpdateTransform();
}

void Enemy::Draw()
{
	DrawAllModel();
}

void Enemy::DebugGUI()
{
#ifdef _DEBUG

	ImGui::Begin("Enemy");

	ImGui::DragFloat3("scale", &transformBase_.scale_.x, 0.01f);
	ImGui::DragFloat3("rotate", &transformBase_.rotate_.x, 0.01f);
	ImGui::DragFloat3("translate", &transformBase_.translate_.x, 1.0f);
	ImGui::DragFloat3("velocity", &velocity.x, 1.0f);
	ImGui::End();

#endif // _DEBUG

}

void Enemy::InitializeWorldTransforms()
{
	for (size_t i = 0; i < kEnemyCount; i++) {
		WorldTransform wt = WorldTransform();
		transforms_.push_back(wt);
	}

	// プレイヤー自身のワールド変換データ
	transformBase_.Initialize();
	transformBase_.scale_ = { 0.5f,0.5f,0.5f };
	transformBase_.translate_ = kPopPosition;

	// Body のワールド変換データ
	transforms_[kEnemyBody].Initialize();
	transforms_[kEnemyBody].SetParent(&transformBase_);
	//  Head のワールド変換データ
	// worldTransformHead_.Initialize();
	transforms_[kEnemyHead].Initialize();
	transforms_[kEnemyHead].SetParent(&transforms_[kEnemyBody]);
	//transforms_[kPlayerHead].scale_ = { 0.3f,0.3f,0.3f };
	transforms_[kEnemyHead].translate_.y = 3.2f;
}

void Enemy::UpdateMovement()
{
	Vector3 pos = transformBase_.GetWorldPos();
	if (pos.x < kPopPosition.x - kMovementRange.x ||
		kPopPosition.x + kMovementRange.x < pos.x) {
		velocity.x *= -1;
	}
	transformBase_.translate_ += velocity;
}

