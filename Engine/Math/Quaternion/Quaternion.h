#pragma once

class Vector3;
class Matrix4x4;


class Quaternion final
{
public:	///	メンバ変数
	float x;
	float y;
	float z;
	float w;

public:

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector3& vector, float scalar);

	Quaternion operator+(const Quaternion& q)const;
	Quaternion operator-()const;
	Quaternion operator*(const Quaternion& q)const;
	Quaternion operator*(float f)const;
	friend Quaternion operator*(float f, const Quaternion& q);

	/// <summary>
	/// ベクトル部を取得
	/// </summary>
	inline Vector3 xyz()const;

public:

	/// <summary>
	/// Quaternion の内積
	/// </summary>
	/// <returns></returns>
	static float Dot(const Quaternion& q1, const Quaternion& q2);
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
	/// <summary>
	/// 任意軸回転を表す Quaternion
	/// </summary>
	/// <param name="axis">軸</param>
	/// <param name="angle">角度</param>
	/// <returns></returns>
	static Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
	/// <summary>
	/// ベクトルを Quaternion で回転させた結果のベクトル
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="q">Quaternion</param>
	/// <returns></returns>
	static Vector3 RotateVector(const Vector3& vector, const Quaternion& q);
	/// <summary>
	/// Quaternion から回転行列を得る
	/// </summary>
	/// <param name="q"></param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateMatrix(const Quaternion& q);
	/// <summary>
	/// Quaternion の球面線形補間
	/// </summary>
	/// <param name="q0">Quaternion</param>
	/// <param name="q1">Quaternion</param>
	/// <param name="t">補間</param>
	/// <returns></returns>
	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);
};