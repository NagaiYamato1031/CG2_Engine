#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include <cstdint>
#include "../Math/Math.h"

class ViewProjection
{
	/// <summary>
	/// メンバ変数
	/// </summary>
public: // パブリック変数
	Vector3 rotate_ = { 0.0f,0.0f,0.0f };
	Vector3 translate_ = { 0.0f,0.0f,0.0f };

private: // プライベート変数
	Vector3 scale_ = { 1.0f,1.0f,1.0f };
	// 行列
	Matrix4x4 matView_;
	Matrix4x4 matProjection_;
	Matrix4x4 matViewProjection_;

	int32_t width_ = 1280;
	int32_t height_ = 720;

	float fovY_ = 0.45f;
	float aspectRatio_ = 1.0f;
	Vector2 nearFar_ = { 0.1f,100.0f };

	/// <summary>
	/// メンバ関数
	/// </summary>
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ViewProjection();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	const Matrix4x4& GetViewMatrix();
	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>プロジェクション行列</returns>
	const Matrix4x4& GetProjectionMatrix();
	/// <summary>
	/// 行列取得
	/// </summary>
	/// <returns>ビュープロジェクション行列</returns>
	const Matrix4x4& GetViewProjectionMatrix();

	void SetFovY(float fovY) { fovY_ = fovY; }
	void SetaspectRatio(float a) { aspectRatio_ = a; }

	void SetNear(float n) { nearFar_.x = n; }
	void SetFar(float f) { nearFar_.y = f; }
	void SetNearFar(const Vector2& nf) { nearFar_ = nf; }

	void SetWidth(int32_t width) { width_ = width; }
	void SetHeight(int32_t height) { height_ = height; }
	void SetSize(const Vector2& size) {
		width_ = static_cast<int32_t>(size.x);
		height_ = static_cast<int32_t>(size.y);
		aspectRatio_ = static_cast<float>(width_) / static_cast<float>(height_);
	}
};