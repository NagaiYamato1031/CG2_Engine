#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include <cstdint>
#include "../Math/Math.h"

class WorldTransform
{
	/// <summary>
	/// メンバ変数
	/// </summary>
public: // パブリック変数
	Vector3 scale_ = { 1.0f,1.0f,1.0f };
	Vector3 rotate_ = { 0.0f,0.0f,0.0f };
	Vector3 translate_{ 0.0f,0.0f,0.0f };


private: // プライベート変数
	// コンスタントバッファ
	//Microsoft::WRL::ComPtr<ID3D12Resource> cBuff_;
	// ワールド行列
	Matrix4x4 matWorld_;

	// 親
	WorldTransform* parent_ = nullptr;

	// ビットでペアレント設定のフラグを管理
	// s : r : t
	uint8_t parentFlag_ = 0b111;

	/// <summary>
	/// メンバ関数
	/// </summary>
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WorldTransform();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const Matrix4x4& GetMatrix();
	Matrix4x4 GetMatrix(uint8_t flag);

	void SetParent(WorldTransform* parent, uint8_t flag = 0b111) { parent_ = parent; parentFlag_ = flag; };
	WorldTransform* GetParent() { return parent_; };
	void SetParentFlag(uint8_t flag) { parentFlag_ = flag; }
	Vector3 GetWorldPos();
	Vector3 GetScale();
};