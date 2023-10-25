#include "WorldTransform.h"

#include "../../Base/DirectXCommon.h"

WorldTransform::WorldTransform() {
	Initialize();
}

void WorldTransform::Initialize() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,0.0f };
	cBuff_.Reset();
	matWorld_ = nullptr;
	MapData();
}

void WorldTransform::CreateConstBuffer() {

	cBuff_.Reset();

	cBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(Matrix4x4));
	cBuff_->Map(0, nullptr, reinterpret_cast<void**>(&matWorld_));
}

const Matrix4x4& WorldTransform::GetMatrix()
{
	*matWorld_ = Matrix4x4::MakeAffineMatrix(scale_, rotate_, translate_);

	if (parent_) {
		*matWorld_ = parent_->GetMatrix() * *matWorld_;
	}

	return *matWorld_;
}

void WorldTransform::MapData()
{
	cBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(Matrix4x4));
	cBuff_->Map(0, nullptr, reinterpret_cast<void**>(&matWorld_));
	*matWorld_ = Matrix4x4::MakeIdentity4x4();
}
