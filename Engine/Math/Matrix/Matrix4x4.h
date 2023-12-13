#pragma once

class Vector2;
class Vector3;
class Vector4;

/// <summary>
/// Matrix4x4
/// </summary>
class Matrix4x4 final
{
public:	///	メンバ変数
	float m[4][4];

public:	///	演算子オーバーロード

	Matrix4x4 operator+(const Matrix4x4& obj) const;
	Matrix4x4 operator-(const Matrix4x4& obj) const;
	Matrix4x4 operator*(const Matrix4x4& obj) const;
	Matrix4x4 operator*(float scalar) const;
	friend Matrix4x4 operator*(float scalar, const Matrix4x4& obj);

	const Matrix4x4& operator+=(const Matrix4x4& obj);
	const Matrix4x4& operator-=(const Matrix4x4& obj);
	const Matrix4x4& operator*=(float scalar);

	/// <summary>
	/// 行列の加算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns>加算された行列</returns>
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 行列の減算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns>減算された行列</returns>
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 行列の乗算
	/// </summary>
	/// <param name="m1">行列１</param>
	/// <param name="m2">行列２</param>
	/// <returns><乗算された行列/returns>
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& matrix);

	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>転置行列</returns>
	static Matrix4x4 Transpose(const Matrix4x4& matrix);

	/// <summary>
	/// 4x4 単位行列
	/// </summary>
	/// <returns>4x4 単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 4x4 平行移動行列
	/// </summary>
	/// <param name="translate">移動ベクトル</param>
	/// <returns>4x4 平行移動行列</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
	
	/// <summary>
	/// 4x4 拡縮行列
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <returns>4x4 拡縮行列</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// X 軸回転行列
	/// </summary>
	/// <param name="radian">X の回転角</param>
	/// <returns>X 軸回転行列</returns>
	static Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// Y 軸回転行列
	/// </summary>
	/// <param name="radian">Y の回転角</param>
	/// <returns>Y 軸回転行列</returns>
	static Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// Z 軸回転行列
	/// </summary>
	/// <param name="radian">Z の回転角</param>
	/// <returns>Z 軸回転行列</returns>
	static Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// 回転行列
	/// </summary>
	/// <param name="radian">XYZ の回転角</param>
	/// <returns>回転行列</returns>
	static Matrix4x4 MakeRotateXYZMatrix(const Vector3& radian);

	/// <summary>
	/// 任意軸回転行列
	/// </summary>
	/// <param name="axis">軸</param>
	/// <param name="angle">回転角</param>
	/// <returns>任意軸回転行列</returns>
	static Matrix4x4 MakeRotateAxisMatrix(const Vector3& axis, float angle);


	/// <summary>
	/// 法線から法線へ向きを変える行列
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	static Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);


	/// <summary>
	/// 4x4 アフィン行列
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">移動</param>
	/// <returns>4x4 アフィン行列</returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// 透視変換行列
	/// </summary>
	/// <param name="fovY">画角</param>
	/// <param name="aspectRatio">アスペクト比</param>
	/// <param name="nearClip">近平面</param>
	/// <param name="farClip">遠平面</param>
	/// <returns></returns>
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

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
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="leftTop">左上</param>
	/// <param name="rightBottom">右下</param>
	/// <param name="nearFar">近遠</param>
	/// <returns>正射影行列</returns>
	static Matrix4x4 MakeOrthographicMatrix(const Vector2& leftTop, const Vector2& rightBottom, const Vector2& nearFar);

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
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minD, float maxD);
	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="leftTop">左上座標</param>
	/// <param name="size">サイズ</param>
	/// <param name="depth">深度バッファ</param>
	/// <returns>ビューポート行列</returns>
	static Matrix4x4 MakeViewportMatrix(const Vector2& leftTop, const Vector2& size, const Vector2& depth);
	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="info">左上座標、サイズの情報</param>
	/// <param name="depth">深度バッファ</param>
	/// <returns>ビューポート行列</returns>
	static Matrix4x4 MakeViewportMatrix(const Vector4& info, const Vector2& depth);
};