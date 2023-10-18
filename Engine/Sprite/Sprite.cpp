#include "Sprite.h"

#include <cassert>
#include "SpriteCommon.h"

void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	assert(spriteCommon);
	spriteCommon_ = spriteCommon;
}
