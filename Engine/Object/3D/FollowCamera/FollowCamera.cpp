#include "FollowCamera.h"

#include "../../../Input/Input.h"
#include "../../../ImGui/ImGuiManager.h"

void FollowCamera::Initialize() {
	viewProjection_.Initialize();
	viewProjection_.rotate_.x = 0.2f;

	GlobalConfigs* configs = GlobalConfigs::GetInstance();
	configs->CreateGroup("FollowCamera");
	configs->AddItem("FollowCamera", "LerpRate", cLerpRate_);
	cLerpRate_ = configs->GetFloatValue("FollowCamera", "LerpRate");
}

void FollowCamera::Update() {

	DebugGUI();

	XINPUT_STATE joyState;

	// 回転速度
	const float kRotate = 0.03f;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		destinationAngleY_ += static_cast<float>(joyState.Gamepad.sThumbRX) / SHRT_MAX * kRotate;
		viewProjection_.rotate_.x -= static_cast<float>(joyState.Gamepad.sThumbRY) / SHRT_MAX * kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		destinationAngleY_ -= kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		destinationAngleY_ += kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		viewProjection_.rotate_.x -= kRotate * 0.75f;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		viewProjection_.rotate_.x += kRotate * 0.75f;
	}

	viewProjection_.rotate_.y = LerpShortAngle(viewProjection_.rotate_.y, destinationAngleY_, cLerpRate_);

	if (target_) {
		interTarget_ = Lerp(interTarget_, target_->GetWorldPos(), cLerpRate_);

		Vector3 offset = CalcOffset();

		viewProjection_.translate_ = interTarget_ + offset;
	}
	// ビュー行列の更新
	//viewProjection_.UpdateMatrix();
}

void FollowCamera::Reset()
{
	if (target_) {
		interTarget_ = target_->GetWorldPos();
		viewProjection_.rotate_.y = target_->rotate_.y;
	}
	destinationAngleY_ = viewProjection_.rotate_.y;

	Vector3 offset = CalcOffset();
	viewProjection_.translate_ = interTarget_ + offset;

}

Vector3 FollowCamera::CalcOffset() const
{
	// 追従対象からカメラまでのオフセット
	Vector3 offset{ 0.0f, 2.0f, -30.0f };

	Matrix4x4 matRotate = Matrix4x4::MakeRotateXYZMatrix(viewProjection_.rotate_);

	offset = Vector3::TransformNormal(offset, matRotate);

	return offset;
}

void FollowCamera::DebugGUI()
{
#ifdef _DEBUG

	ImGui::Begin("FollowCamera");

	ImGui::SliderFloat("LerpRate", &cLerpRate_, 0.01f,1.0f);

	ImGui::Separator();

	if (ImGui::Button("ApplyConfig")) {
		cLerpRate_ = GlobalConfigs::GetInstance()->GetFloatValue("FollowCamera", "LerpRate");
	}

	ImGui::End();

#endif // _DEBUG

}
