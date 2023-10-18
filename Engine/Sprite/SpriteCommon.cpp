#include "SpriteCommon.h"

#include <cassert>

SpriteCommon* SpriteCommon::GetInstance() {
	static SpriteCommon instance;
	return &instance;
}

void SpriteCommon::Initialize(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	dxCommon_ = dxCommon;
}


void SpriteCommon::PreDraw() {
}

void SpriteCommon::PostDraw() {
}
