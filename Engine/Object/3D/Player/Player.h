#pragma once

#include <optional>

#include "../BaseCharacter.h"
#include "../../../Input/Input.h"
#include "../../../Shape/AABB.h"

class Player final : public BaseCharacter
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

		kPlayerWeapon,

		kPlayerCount,
	};

	enum BEHAVIOR {
		kROOT,
		kDASH,
		kATTACK,

		kBEHAVIOR_COUNT
	};

	// プライベートサブクラス
private:

	struct WorkDash
	{
		int32_t cFrameOfDash_ = 12;
		float cDashPower_ = 7.0f;

		int32_t dashParameter_ = 0;
		Vector3 velocity_{ 0.0f,0.0f,0.0f };
	};

	struct WorkAttack
	{
		int32_t cFrameOfAttack_ = 40;

		int32_t attackParameter_ = 0;

		Collider* collider_;
	};


/// <summary>
/// プライベートメンバ変数
/// </summary>
private:

	// キーボード入力
	Input* input_ = nullptr;

	AABB colliderAABB_;
	AABB goalAABB_;

	AABB* collisionAABB_ = nullptr;
	AABB* preCollisionAABB_ = nullptr;

	Vector3 velocity;

	bool isJumpEnable_ = true;
	bool isCollision_ = false;


	void(Player::* pFunc_[kBEHAVIOR_COUNT])();

	BEHAVIOR behavior_ = BEHAVIOR::kROOT;
	std::optional<BEHAVIOR> behaviorRequest_ = std::nullopt;

	// 各関数内の変数


	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	// 浮遊時のサイクルフレーム
	int floatingCycle_ = 60;

	// 浮遊時の振幅
	float floatingAmplitude_ = 0.1f;

	// ダッシュ変数
	WorkDash workDash_;

	// アタック変数
	WorkAttack workAttack_;


/// <summary>
/// オーバーライド
/// </summary>
public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;
	void Update(std::vector<AABB*>& floors);

	void Draw() override;

	void ApplyConfig() override;
	void StorageConfig() override;

	void DebugGUI() override;
	
	Vector3 GetCenterPosition() override;

	void OnCollisionEnter() override;
	void OnCollision() override;
	void OnCollisionExit() override;

/// <summary>
/// プライベートメンバ関数
/// </summary>
private:

	void InitializeWorldTransforms();


	void TranslateReset();

	// 入力検知
	void GetOperate();

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();

	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	void InitRoot();
	void InitDash();
	void InitAttack();


	// 関数テーブル
	void Root();
	void Dash();
	void Attack();

};