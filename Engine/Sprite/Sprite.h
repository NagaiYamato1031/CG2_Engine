#pragma once

class SpriteCommon;

class Sprite
{
private: // メンバ変数

	SpriteCommon* spriteCommon_ = nullptr;

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spriteCommon);
};

