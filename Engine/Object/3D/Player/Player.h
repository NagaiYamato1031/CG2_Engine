#pragma once

#include "../../IObject.h"
#include "../../../Input/Input.h"
#include "../../../Shape/AABB.h"

class Player final : public IObject
{
/// <summary>
/// サブクラス
/// </summary>
private:

	enum PartsIndex {
		kPlayerBody,
		kPlayerHead,
		kPlayerL_arm,
		kPlayerR_arm,

		kPlayerCount,
	};


/// <summary>
/// プライベートメンバ変数
/// </summary>
private:

	// キーボード入力
	Input* input_ = nullptr;

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	// 浮遊時のサイクルフレーム
	int floatingCycle_ = 60;

	// 浮遊時の振幅
	float floatingAmplitude_ = 0.1f;

	AABB colliderAABB_;
	AABB goalAABB_;

	AABB* collisionAABB_ = nullptr;
	AABB* preCollisionAABB_ = nullptr;

	Vector3 velocity;

	bool isJumpEnable_ = true;
	bool isCollision_ = false;


/// <summary>
/// オーバーライド
/// </summary>
public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;
	void Update(std::vector<AABB*>& floors);

	void Draw() override;

	void DebugGUI() override;
	
/// <summary>
/// プライベートメンバ関数
/// </summary>
private:

	void InitializeWorldTransforms();

	void OnCollisionEnter();
	void OnCollision();
	void OnCollisionExit();

	void TranslateReset();

	// 入力検知
	void GetOperate();

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();

	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

};