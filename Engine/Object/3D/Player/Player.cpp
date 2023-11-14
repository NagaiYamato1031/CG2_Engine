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
	colliderAABB_.transform_.Initialize();
	colliderAABB_.transform_.SetParent(&transformBase_);
	colliderAABB_.min_ = { -0.5f,0.0f,-0.5f };
	colliderAABB_.max_ = { 0.5f,0.7f,0.5f };
	goalAABB_.transform_.Initialize();
	goalAABB_.transform_.translate_ = { -20.0f,14.0f,60.0f };
	goalAABB_.min_ = { -0.5f,-0.7f,-0.5f };
	goalAABB_.max_ = { 0.5f,0.7f,0.5f };
	velocity = { 0.0f,0.0f,0.0f, };
	isJumpEnable_ = true;
	isCollision_ = false;

	// 当たり判定
	SetRadius(1.0f);

	workAttack_.collider_ = new Collider();

	// 振る舞いテーブル
	pFunc_[kROOT] = &Player::Root;
	pFunc_[kDASH] = &Player::Dash;
	pFunc_[kATTACK] = &Player::Attack;

	configs_ = GlobalConfigs::GetInstance();
	const char* groupName = "Player";
	configs_->CreateGroup(groupName);

	StorageConfig();
	ApplyConfig();
}

void Player::Update()
{

}

void Player::Update(std::vector<AABB*>& aabbs_)
{
	DebugGUI();

	if (behaviorRequest_) {
		behavior_ = behaviorRequest_.value();
		switch (behavior_)
		{
		case Player::kROOT:
			InitRoot();
			break;
		case Player::kDASH:
			InitDash();
			break;
		case Player::kATTACK:
			InitAttack();
			break;
		case Player::kBEHAVIOR_COUNT:
		default:
			behavior_ = kROOT;
			InitializeFloatingGimmick();
			break;
		}
		behaviorRequest_ = std::nullopt;
	}

	(this->*pFunc_[behavior_])();


	transformBase_.translate_ += velocity;

	// 当たり判定
	/*if (colliderAABB_.IsCollision(aabbs_[0])) {
		TranslateReset();
	}*/
	if (colliderAABB_.IsCollision(&goalAABB_)) {
		TranslateReset();
	}
	preCollisionAABB_ = collisionAABB_;
	collisionAABB_ = colliderAABB_.IsCollision(aabbs_.data(), aabbs_.size());
	if (collisionAABB_) {
		if (!preCollisionAABB_) {
			OnCollisionEnter();
		}
		/*else {
			OnCollision();
		}*/
	}
	else if (preCollisionAABB_) {
		OnCollisionExit();
	}
	else {
		velocity.y -= 0.05f;
		isJumpEnable_ = false;
	}
	// 落ちた時
	if (transformBase_.translate_.y < -20.0f) {
		TranslateReset();
	}

	UpdateTransform();

}

void Player::Draw()
{
	for (size_t i = 0; i < transforms_.size(); i++)
	{
		if (i == transforms_.size() - 1 && behavior_ != kATTACK) {
			continue;
		}
		models_[i]->Draw(&transforms_[i], viewProjection_);
	}
	models_.back()->Draw(&goalAABB_.transform_, viewProjection_);
}


void Player::ApplyConfig()
{
	const char* groupName = "Player";

	workDash_.cFrameOfDash_ = configs_->GetIntValue(groupName, "FrameOfDash");
	workDash_.cDashPower_ = configs_->GetFloatValue(groupName, "DashPower");

	workAttack_.cFrameOfAttack_ = configs_->GetIntValue(groupName, "FrameOfAttack");
}

void Player::StorageConfig()
{
	const char* groupName = "Player";
	configs_->AddItem(groupName, "FrameOfDash", workDash_.cFrameOfDash_);
	configs_->AddItem(groupName, "DashPower", workDash_.cDashPower_);

	configs_->AddItem(groupName, "FrameOfAttack", workAttack_.cFrameOfAttack_);

}

void Player::DebugGUI()
{
#ifdef _DEBUG

	ImGui::Begin("Player");

	ImGui::DragFloat3("scale", &transformBase_.scale_.x, 0.01f);
	ImGui::DragFloat3("rotate", &transformBase_.rotate_.x, 0.01f);
	ImGui::DragFloat3("translate", &transformBase_.translate_.x, 1.0f);
	Vector3 worldPos = transformBase_.GetWorldPos();
	ImGui::DragFloat3("worldPosition", &worldPos.x, 1.0f);
	ImGui::DragFloat3("velocity", &velocity.x, 1.0f);

	ImGui::Separator();

	ImGui::Checkbox("isCollision", &isCollision_);
	ImGui::Text("Behavior : %d", behavior_);

	ImGui::Separator();

	if (ImGui::Button("ApplyConfig")) {
		ApplyConfig();
	}

	ImGui::End();

#endif // _DEBUG

}

Vector3 Player::GetCenterPosition()
{
	const Vector3 offset = { 0.0f,1.5f,0.0f };

	Vector3 centerPos = Vector3::Transform(offset, transformBase_.GetMatrix());
	return centerPos;
}

void Player::InitializeWorldTransforms()
{
	for (size_t i = 0; i < kPlayerCount; i++) {
		WorldTransform wt = WorldTransform();
		transforms_.push_back(wt);
	}

	// プレイヤー自身のワールド変換データ
	transformBase_.Initialize();
	transformBase_.scale_ = { 0.5f,0.5f,0.5f };
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

	transforms_[kPlayerWeapon].Initialize();
	transforms_[kPlayerWeapon].SetParent(&transforms_[kPlayerBody]);
}

void Player::OnCollisionEnter()
{
	Vector3 temp = transformBase_.GetWorldPos() - collisionAABB_->transform_.GetWorldPos();
	transformBase_.translate_ = temp;
	transformBase_.SetParent(&collisionAABB_->transform_, 0b001);
	if (velocity.y < 0) {
		velocity.y = 0.0f;
		transformBase_.translate_.y = 0.0f;
	}
	isCollision_ = true;
	isJumpEnable_ = true;
}

void Player::OnCollision()
{
	TranslateReset();
}

void Player::OnCollisionExit()
{
	transformBase_.translate_ = transformBase_.GetWorldPos();
	transformBase_.SetParent(nullptr);

	isCollision_ = false;
	isJumpEnable_ = false;
}

void Player::TranslateReset()
{
	transformBase_.translate_ = { 0.0f,5.0f,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	transformBase_.SetParent(nullptr);
	behaviorRequest_ = kROOT;
}

void Player::GetOperate()
{
	// 速さ
	const float kSpeed = 0.3f;
	// 移動成分
	Vector3 move = { 0.0f, velocity.y, 0.0f };

	XINPUT_STATE joyState;
	if (input_->GetJoystickState(0, joyState)) {
		move.x = static_cast<float>(joyState.Gamepad.sThumbLX) / SHRT_MAX * kSpeed;
		move.z = static_cast<float>(joyState.Gamepad.sThumbLY) / SHRT_MAX * kSpeed;
	}

	if (input_->PushKey(DIK_W)) {
		move.z = kSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.z = -kSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = kSpeed;
	}
	if (input_->PushKey(DIK_A)) {
		move.x = -kSpeed;
	}



	if (move.x != 0.0f || move.z != 0.0f) {
		// 回転方向に合わせる
		Matrix4x4 matRotate = Matrix4x4::MakeRotateYMatrix(viewProjection_->rotate_.y);

		move = Vector3::TransformNormal(move, matRotate);
		// 進行方向に向けて回転する
		transformBase_.rotate_.y = std::atan2(move.x, move.z);

	}
	// 移動
	velocity = move;

	if (isJumpEnable_ && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		velocity.y = 0.7f;
		isJumpEnable_ = false;
		isCollision_ = false;
	}
	if (isJumpEnable_ && input_->TriggerKey(DIK_SPACE)) {
		velocity.y = 0.7f;
		isJumpEnable_ = false;
		isCollision_ = false;
	}

	if (input_->TriggerKey(DIK_Q)) {
		behaviorRequest_ = kATTACK;
	}
	if (input_->TriggerKey(DIK_E)) {
		behaviorRequest_ = kDASH;
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

void Player::InitRoot()
{
	transforms_[kPlayerL_arm].rotate_.x = 0.0f;
	transforms_[kPlayerR_arm].rotate_.x = 0.0f;
	InitializeFloatingGimmick();
}

void Player::InitDash()
{
	workDash_.dashParameter_ = 0;
	float theta = transformBase_.rotate_.y;
	Vector3 direct = { std::sinf(theta), 0.0f,std::cosf(theta) };
	workDash_.velocity_ = direct * workDash_.cDashPower_;
}

void Player::InitAttack()
{
	workAttack_.attackParameter_ = 0;
	transforms_[kPlayerWeapon].rotate_.x = 1.5f;
	velocity = { 0.0f,0.0f,0.0f };
}

void Player::Root()
{
	GetOperate();

	UpdateFloatingGimmick();
}

void Player::Dash()
{
	// 足す
	workDash_.dashParameter_++;

	velocity = workDash_.velocity_;

	// ルートに戻る
	if (workDash_.cFrameOfDash_ <= workDash_.dashParameter_) {
		behaviorRequest_ = kROOT;
	}
}

void Player::Attack()
{
	// 足す
	workAttack_.attackParameter_++;

	float theta = Lerp(0.0f, 1.4f, (workAttack_.attackParameter_ / (float)workAttack_.cFrameOfAttack_));
	// 武器を振る
	transforms_[kPlayerWeapon].rotate_.x = theta;
	transforms_[kPlayerL_arm].rotate_.x = -3.14f + theta;
	transforms_[kPlayerR_arm].rotate_.x = -3.14f + theta;

	if (workAttack_.cFrameOfAttack_ / 3 < workAttack_.cFrameOfAttack_) {

	}

	// 戻す
	if (workAttack_.cFrameOfAttack_ <= workAttack_.attackParameter_) {
		behaviorRequest_ = kROOT;
	}
}
