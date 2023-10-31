#include "FollowCamera.h"
#include "../../../Input/Input.h"


void FollowCamera::Initialize() { viewProjection_.Initialize(); }

void FollowCamera::Update() {
	//XINPUT_STATE joyState;

	// 回転速度
	const float kRotate = 0.03f;

	//if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	//	viewProjection_.rotate_.y += static_cast<float>(joyState.Gamepad.sThumbRX) / SHRT_MAX * kRotate;
	//	viewProjection_.rotate_.x -= static_cast<float>(joyState.Gamepad.sThumbRY) / SHRT_MAX * kRotate;
	//}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		viewProjection_.rotate_.y -= kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		viewProjection_.rotate_.y += kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		viewProjection_.rotate_.x -= kRotate;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		viewProjection_.rotate_.x += kRotate;
	}


	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset{ 0.0f, 4.0f, -20.0f };

		Matrix4x4 matRotate = Matrix4x4::MakeRotateXYZMatrix(viewProjection_.rotate_);

		offset = Vector3::TransformNormal(offset, matRotate);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translate_ = target_->translate_ + offset;
	}
	// ビュー行列の更新
	//viewProjection_.UpdateMatrix();
}