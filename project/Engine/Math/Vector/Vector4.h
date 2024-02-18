#pragma once

class Vector2;
class Vector3;
class Matrix3x3;
class Matrix4x4;


/// <summary>
/// Vector4
/// </summary>
class Vector4 final
{
public:	///	メンバ変数
	float x;
	float y;
	float z;
	float w;

public:	///	演算子オーバーロード

	Vector4 operator+(const Vector4& obj);
	Vector4 operator-(const Vector4& obj);
	Vector4 operator*(float scalar);
	friend Vector4 operator*(float scalar, const Vector4& obj);
	Vector4 operator*(const Matrix4x4& matrix);
	Vector4 operator/(float scalar);

	const Vector4& operator+=(const Vector4& obj);
	const Vector4& operator-=(const Vector4& obj);
	const Vector4& operator*=(float scalar);
	const Vector4& operator/=(float scalar);


	/// <summary>
	/// ベクトルの乗算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>乗算されたベクトル</returns>
	Vector4 Multiply(const Vector4& v, const Matrix4x4& matrix);

	/// <summary>
	/// ベクトルの内積
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <returns>内積</returns>
	float Dot(const Vector4& v1, const Vector4& v2);

	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	float Length(const Vector4& v);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	Vector4 Normalize(const Vector4& v);

};