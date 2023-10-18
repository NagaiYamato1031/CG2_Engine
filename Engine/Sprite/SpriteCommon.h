#pragma once
#include "../Base/DirectXCommon.h"
#include "Sprite.h"

class SpriteCommon
{
public: // メンバ関数
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	static SpriteCommon* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画語処理
	/// </summary>
	void PostDraw();

private: // メンバ変数

private: // コピー禁止

	SpriteCommon() = default;
	~SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	const SpriteCommon& operator=(const SpriteCommon&) = delete;

private: // 非公開のメンバ関数

	DirectXCommon* dxCommon_ = nullptr;

};

