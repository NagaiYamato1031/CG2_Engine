#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include "../../Math/Math.h"

class WorldTransform
{
	/// <summary>
	/// メンバ変数
	/// </summary>
public: // パブリック変数
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;

private: // プライベート変数
	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> cBuff_;
	// ワールド行列
	Matrix4x4* matWorld_ = nullptr;

	// 親
	WorldTransform* parent_ = nullptr;

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
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const Matrix4x4& GetMatrix() { return *matWorld_; }

	void SetParent(WorldTransform* parent) { parent_ = parent; };
	WorldTransform* GetParent() { return parent_; };

private:

	/// <summary>
	/// マッピングする
	/// </summary>
	void MapData();



};