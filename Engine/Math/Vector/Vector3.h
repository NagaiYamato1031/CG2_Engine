#pragma once

class Vector2;
class Vector4;
class Matrix3x3;
class Matrix4x4;

//struct Segment;

/// <summary>
/// Vector3
/// </summary>
class Vector3 final
{
public:	///	メンバ変数
	float x;
	float y;
	float z;

public:	///	演算子オーバーロード

	Vector3 operator+(const Vector3& obj) const;
	Vector3 operator-(const Vector3& obj) const;
	friend Vector3 operator-(const Vector3& obj);
	Vector3 operator*(float scalar) const;
	friend Vector3 operator*(float scalar, const Vector3& obj);
	Vector3 operator*(const Matrix3x3& matrix) const;
	//friend Vector3 operator*(const Matrix3x3& matrix, const Vector3& obj);
	Vector3 operator/(float scalar) const;

	const Vector3& operator+=(const Vector3& obj);
	const Vector3& operator-=(const Vector3& obj);
	const Vector3& operator*=(float scalar);
	const Vector3& operator/=(float scalar);

	/// <summary>
	/// ベクトルと行列の乗算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>乗算されたベクトル</returns>
	static Vector3 Multiply(const Vector3& v, const Matrix3x3& matrix);

	/// <summary>
	/// ベクトルの内積
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <returns>内積</returns>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトルのクロス積
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <returns>クロス積</returns>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	static float Length(const Vector3& v);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="vector">座標</param>
	/// <param name="matrix">行列</param>
	/// <returns>変換座標</returns>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	///	ベクトル変換
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="m">行列</param>
	/// <returns>変換ベクトル</returns>
	static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

	/// <summary>
	/// ベクトル射影
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <returns>正射影ベクトル</returns>
	static Vector3 Project(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 最近接点を求める
	/// </summary>
	/// <param name="point">始点</param>
	/// <param name="segment">線分</param>
	/// <returns>始点に最も近い線分 t の座標</returns>
	//static Vector3 CrossestPoint(const Vector3& point, const Segment& segment);

	/// <summary>
	/// 垂直を求める
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>垂直なベクトル</returns>
	static Vector3 Perpendicular(const Vector3& vector);

};