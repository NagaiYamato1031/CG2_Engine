#pragma once


class Vector3;
class Vector4;
class Matrix3x3;
class Matrix4x4;



/// <summary>
/// Vector2
/// </summary>
class Vector2 final
{
public:	///	メンバ変数
	float x;
	float y;

public:	///	演算子オーバーロード

	Vector2 operator+(const Vector2& obj)const;
	Vector2 operator-(const Vector2& obj)const;
	Vector2 operator*(float scalar);
	friend Vector2 operator*(float scalar, const Vector2& obj);
	Vector2 operator/(float scalar)const;

	const Vector2& operator+=(const Vector2& obj);
	const Vector2& operator-=(const Vector2& obj);
	const Vector2& operator*=(float scalar);
	const Vector2& operator/=(float scalar);


	/// <summary>
	/// ベクトルの内積
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <returns>内積</returns>
	float Dot(const Vector2& v1, const Vector2& v2);

	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	float Length(const Vector2& v);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	Vector2 Normalize(const Vector2& v);

	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="vector">座標</param>
	/// <param name="matrix">行列</param>
	/// <returns>変換座標</returns>
	Vector2 Transform(const Vector2& vector, const Matrix3x3& matrix);

};