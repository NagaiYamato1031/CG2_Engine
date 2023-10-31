#include "ViewProjection.h"

#include "../Base/DirectXCommon.h"

ViewProjection::ViewProjection() {
	Initialize();
}

void ViewProjection::Initialize() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,1.0f,-10.0f };
	matView_ = Matrix4x4::MakeIdentity4x4();
	matProjection_ = Matrix4x4::MakeIdentity4x4();
	matViewProjection_ = Matrix4x4::MakeIdentity4x4();

	fovY_ = 0.45f;
	width_ = WinApp::GetInstance()->GetClientWidth();
	height_ = WinApp::GetInstance()->GetClientHeight();
	aspectRatio_ = static_cast<float>(width_) / static_cast<float>(height_);
	nearFar_ = { 0.1f,100.0f };
}

const Matrix4x4& ViewProjection::GetViewMatrix()
{
	matView_ = Matrix4x4::MakeAffineMatrix(scale_, rotate_, translate_);
	matView_ = Matrix4x4::Inverse(matView_);
	return matView_;
}

const Matrix4x4& ViewProjection::GetProjectionMatrix()
{
	matProjection_ = Matrix4x4::MakePerspectiveFovMatrix(fovY_, aspectRatio_, nearFar_.x, nearFar_.y);

	return matProjection_;
}

const Matrix4x4& ViewProjection::GetViewProjectionMatrix()
{
	matViewProjection_;
	matView_ = GetViewMatrix();
	matProjection_ = GetProjectionMatrix();

	matViewProjection_ = matView_ * matProjection_;
	return matViewProjection_;
}