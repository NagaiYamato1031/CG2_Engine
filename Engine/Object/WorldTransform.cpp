#include "WorldTransform.h"

#include "../Base/DirectXCommon.h"

WorldTransform::WorldTransform() {
	Initialize();
}

void WorldTransform::Initialize() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,0.0f };
	//cBuff_.Reset();
	matWorld_ = Matrix4x4::MakeIdentity4x4();
	parent_ = nullptr;
	parentFlag_ = 0b111;
}

const Matrix4x4& WorldTransform::GetMatrix()
{
	matWorld_ = Matrix4x4::MakeAffineMatrix(scale_, rotate_, translate_);
	if (parent_) {
		matWorld_ = matWorld_ * parent_->GetMatrix(parentFlag_);
	}
	return matWorld_;
}

Matrix4x4 WorldTransform::GetMatrix(uint8_t flag)
{
	Matrix4x4 matFlags = Matrix4x4::MakeIdentity4x4();
	if (flag & 0b100) {
		matFlags = matFlags * Matrix4x4::MakeScaleMatrix(scale_);
	}if (flag & 0b010) {
		matFlags = matFlags * Matrix4x4::MakeRotateXYZMatrix(rotate_);
	}if (flag & 0b001) {
		matFlags = matFlags * Matrix4x4::MakeTranslateMatrix(translate_);
	}
	// 親がある場合
	if (parent_) {
		matFlags =matFlags * parent_->GetMatrix(flag);
	}

	return matFlags;
}

Vector3 WorldTransform::GetWorldPos()
{
	Matrix4x4 matWorld = GetMatrix();
	return { matWorld.m[3][0],matWorld.m[3][1],matWorld.m[3][2] };
}

Vector3 WorldTransform::GetScale()
{
	Matrix4x4 matScale = GetMatrix(0b100);
	return { matScale.m[0][0],matScale.m[1][1],matScale.m[2][2] };
}
