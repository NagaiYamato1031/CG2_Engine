#pragma once

class Vector3;

class Quaternion final
{
public:	///	メンバ変数
	float x;
	float y;
	float z;
	float w;

public:

	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector3& vector, float scalar);

	/// <summary>
	/// ベクトル部を取得
	/// </summary>
	inline Vector3 GetVector()const;
	/// <summary>
	/// スカラー部を取得
	/// </summary>
	inline float GetScalar()const;

public:

	/// <summary>
	/// Quaternion の積
	/// </summary>
	static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
	/// <summary>
	/// 単位 Quaternion
	/// </summary>
	/// <returns></returns>
	static Quaternion IdentityQuaternion();
	/// <summary>
	/// 虚部を反転させた Quaternion
	/// 共役 Quaternion
	/// </summary>
	static Quaternion Conjugate(const Quaternion& q);
	/// <summary>
	/// Quaternion の nolm
	/// </summary>
	static float Norm(const Quaternion& q);
	/// <summary>
	/// 正規化した Quaternion
	/// </summary>
	static Quaternion Normalize(const Quaternion& q);
	/// <summary>
	/// 逆 Quaternion
	/// </summary>
	static Quaternion Inverse(const Quaternion& q);


};