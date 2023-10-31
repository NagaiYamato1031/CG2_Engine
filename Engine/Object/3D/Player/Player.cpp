#include "Player.h"

#include <numbers>
#include <cmath>

void Player::Initialize(const std::vector<Model*>& models)
{
	models_ = models;
	transformBase_.Initialize();
	transforms_.clear();
	input_ = Input::GetInstance();
	InitializeWorldTransforms();
	InitializeFloatingGimmick();
}

void Player::Update()
{
	DebugGUI();

	UpdateFloatingGimmick();
	UpdateTransform();
}

void Player::Draw()
{
	DrawAllModel();
}

void Player::DebugGUI()
{
#ifdef _DEBUG

	ImGui::Begin("Player");

	ImGui::DragFloat3("scale", &transformBase_.scale_.x, 0.01f);
	ImGui::DragFloat3("rotate", &transformBase_.rotate_.x, 0.01f);
	ImGui::DragFloat3("translate", &transformBase_.translate_.x, 0.01f);


	ImGui::End();

#endif // _DEBUG

}

void Player::InitializeWorldTransforms()
{
	for (size_t i = 0; i < kPlayerCount; i++) {
		WorldTransform wt = WorldTransform();
		transforms_.push_back(wt);
	}

	// プレイヤー自身のワールド変換データ
	transformBase_.Initialize();
	transformBase_.scale_ = { 0.3f,0.3f,0.3f };
	transformBase_.translate_ = { 0.0f, 0.0f, 0.0f };

	// Body のワールド変換データ
	transforms_[kPlayerBody].Initialize();
	transforms_[kPlayerBody].SetParent(&transformBase_);
	//  Head のワールド変換データ
	// worldTransformHead_.Initialize();
	transforms_[kPlayerHead].Initialize();
	transforms_[kPlayerHead].SetParent(&transforms_[kPlayerBody]);
	//transforms_[kPlayerHead].scale_ = { 0.3f,0.3f,0.3f };
	transforms_[kPlayerHead].translate_.y = 3.2f;
	//  L arm のワールド変換データ
	transforms_[kPlayerL_arm].Initialize();
	transforms_[kPlayerL_arm].SetParent(&transforms_[kPlayerBody]);
	//transforms_[kPlayerL_arm].scale_ = { 0.3f,0.3f,0.3f };
	transforms_[kPlayerL_arm].translate_.x = -1.4f;
	transforms_[kPlayerL_arm].translate_.y = 2.7f;
	//  R arm のワールド変換データ
	transforms_[kPlayerR_arm].Initialize();
	transforms_[kPlayerR_arm].SetParent(&transforms_[kPlayerBody]);
	//transforms_[kPlayerR_arm].scale_ = { 0.3f,0.3f,0.3f };
	transforms_[kPlayerR_arm].translate_.x = 1.4f;
	transforms_[kPlayerR_arm].translate_.y = 2.7f;
}

void Player::GetOperate()
{
	if (input_->PushKey(DIK_A)) {
		transformBase_.translate_.x -= 1.0f;
	}
	if (input_->PushKey(DIK_D)) {
		transformBase_.translate_.x += 1.0f;
	}
	if (input_->PushKey(DIK_W)) {
		transformBase_.translate_.z += 1.0f;
	}
	if (input_->PushKey(DIK_S)) {
		transformBase_.translate_.z -= 1.0f;
	}
}

void Player::InitializeFloatingGimmick()
{
	floatingParameter_ = 0.0f;
}

void Player::UpdateFloatingGimmick()
{
	// 浮遊移動のサイクル<frame>
	// static int floatingCycle = 60;
	// 1 フレームでのパラメータ加算値
	float step = 2.0f * static_cast<float>(std::numbers::pi) / floatingCycle_;

	// パラメータを 1 ステップ分加算
	floatingParameter_ += step;
	// 2 π を超えたら 0 に戻す
	floatingParameter_ =
		std::fmodf(floatingParameter_, 2.0f * static_cast<float>(std::numbers::pi));

	// 浮遊の振幅<m>
	// static float floatingAmplitude_ = 0.5f;
	// 浮遊を座標に変換
	transforms_[kPlayerBody].translate_.y =
		std::sin(floatingParameter_) * floatingAmplitude_;
	// worldTransformBody_.translation_.y = std::sin(floatingParameter_) * amplitude;
	float amplitudeArm = 0.2f;
	transforms_[kPlayerL_arm].rotate_.z = std::sin(floatingParameter_) * amplitudeArm;
	transforms_[kPlayerR_arm].rotate_.z = -std::sin(floatingParameter_) * amplitudeArm;
}
