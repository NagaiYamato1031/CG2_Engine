#pragma once

class Vector2;
class Vector3;
class Vector4;

/// <summary>
/// Matrix3x3
/// </summary>
class Matrix3x3 final
{
public:	///	メンバ変数
	float m[3][3];

public:	///	演算子オーバーロード

	Matrix3x3 operator+(const Matrix3x3& obj) const;
	Matrix3x3 operator-(const Matrix3x3& obj) const;
	Matrix3x3 operator*(const Matrix3x3& obj) const;
	Matrix3x3 operator*(float scalar) const;
	friend Matrix3x3 operator*(float scalar, const Matrix3x3& obj);

	const Matrix3x3& operator+=(const Matrix3x3& obj);
	const Matrix3x3& operator-=(const Matrix3x3& obj);
	const Matrix3x3& operator*=(float scalar);

	/// <summary>
	/// 行列の加算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns>加算された行列</returns>
	Matrix3x3 Add(const Matrix3x3& m1, const Matrix3x3& m2);

	/// <summary>
	/// 行列の減算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns>減算された行列</returns>
	Matrix3x3 Subtract(const Matrix3x3& m1, const Matrix3x3& m2);

	/// <summary>
	/// 行列の乗算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns><乗算された行列/returns>
	Matrix3x3 Multiply(const Matrix3x3& m1, const Matrix3x3& m2);

	/*

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>逆行列</returns>
	Matrix3x3 Inverse(const Matrix3x3& matrix);

	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>転置行列</returns>
	Matrix3x3 Transpose(const Matrix3x3& matrix);

	/// <summary>
	/// 3x3 単位行列
	/// </summary>
	/// <returns>3x3 単位行列</returns>
	Matrix3x3 MakeIdentity3x3();

	/// <summary>
	/// 3x3 平行移動行列
	/// </summary>
	/// <param name="translate">移動ベクトル</param>
	/// <returns>3x3 平行移動行列</returns>
	Matrix3x3 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 3x3 拡縮行列
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <returns>3x3 拡縮行列</returns>
	Matrix3x3 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// X 軸回転行列
	/// </summary>
	/// <param name="radian">X の回転角</param>
	/// <returns>X 軸回転行列</returns>
	Matrix3x3 MakeRotateXMatrix(float radian);

	/// <summary>
	/// Y 軸回転行列
	/// </summary>
	/// <param name="radian">Y の回転角</param>
	/// <returns>Y 軸回転行列</returns>
	Matrix3x3 MakeRotateYMatrix(float radian);

	/// <summary>
	/// Z 軸回転行列
	/// </summary>
	/// <param name="radian">Z の回転角</param>
	/// <returns>Z 軸回転行列</returns>
	Matrix3x3 MakeRotateZMatrix(float radian);

	/// <summary>
	/// 回転行列
	/// </summary>
	/// <param name="radian">XYZ の回転角</param>
	/// <returns>回転行列</returns>
	Matrix3x3 MakeRotateXYZMatrix(const Vector3& radian);

	/// <summary>
	/// 3x3 アフィン行列
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">移動</param>
	/// <returns>3x3 アフィン行列</returns>
	Matrix3x3 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// 透視変換行列
	/// </summary>
	/// <param name="fovY">画角</param>
	/// <param name="aspectRatio">アスペクト比</param>
	/// <param name="nearClip">近平面</param>
	/// <param name="farClip">遠平面</param>
	/// <returns></returns>
	Matrix3x3 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="right">右</param>
	/// <param name="bottom">下</param>
	/// <param name="nearClip">近平面</param>
	/// <param name="farClip">遠平面</param>
	/// <returns>正射影行列</returns>
	Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="leftTop">左上</param>
	/// <param name="rightBottom">右下</param>
	/// <param name="nearFar">近遠</param>
	/// <returns>正射影行列</returns>
	Matrix3x3 MakeOrthographicMatrix(const Vector2& leftTop, const Vector2& rightBottom, const Vector2& nearFar);

	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="minD">最小深度値</param>
	/// <param name="maxD">最大深度値</param>
	/// <returns>ビューポート行列</returns>
	Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height, float minD, float maxD);
	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="leftTop">左上座標</param>
	/// <param name="size">サイズ</param>
	/// <param name="depth">深度バッファ</param>
	/// <returns>ビューポート行列</returns>
	Matrix3x3 MakeViewportMatrix(const Vector2& leftTop, const Vector2& size, const Vector2& depth);
	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="info">左上座標、サイズの情報</param>
	/// <param name="depth">深度バッファ</param>
	/// <returns>ビューポート行列</returns>
	Matrix3x3 MakeViewportMatrix(const Vector4& info, const Vector2& depth);

	*/

};