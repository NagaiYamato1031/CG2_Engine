#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include <cstdint>
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
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const Matrix4x4& GetMatrix();

	void SetParent(WorldTransform* parent) { parent_ = parent; };
	WorldTransform* GetParent() { return parent_; };
	void SetBitFlag(uint8_t flag) { parentFlag_ = flag; }
	//ID3D12Resource* GetResource() { return cBuff_.Get(); }
	//D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() { return cBuff_->GetGPUVirtualAddress(); }

private:

	/// <summary>
	/// マッピングする
	/// </summary>
	void MapData();



};