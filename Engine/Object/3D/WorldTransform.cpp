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
}

void WorldTransform::CreateConstBuffer() {

	cBuff_.Reset();

	cBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(Matrix4x4));
	cBuff_->Map(0, nullptr, reinterpret_cast<void**>(&matWorld_));
}