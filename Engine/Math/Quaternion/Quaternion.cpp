#include "Quaternion.h"

#include <cmath>
#include "../Math.h"

Quaternion::Quaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

Quaternion::Quaternion(const Vector3& vector, float scalar)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = scalar;
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(this->xyz() + q.xyz(), this->w + q.w);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-this->x, -this->y, -this->z, -this->w);
}

Quaternion Quaternion::operator*(const Quaternion& obj) const
{
	return Multiply(*this, obj);
}

Quaternion Quaternion::operator*(float f) const
{
	return Quaternion(f * this->xyz(), f * this->w);
}

Quaternion operator*(float f, const Quaternion& q)
{
	return Quaternion(f * q.xyz(), f * q.w);
}


Vector3 Quaternion::xyz()const
{
	return Vector3(this->x, this->y, this->z);
}

float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

Quaternion Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2)
{
	Vector3 qv = q1.xyz();
	float qw = q1.w;
	Vector3 rv = q2.xyz();
	float rw = q2.w;

	Vector3 vector{};
	float scalar{};

	scalar = qw * rw - Vector3::Dot(qv, rv);
	vector = Vector3::Cross(qv, rv) + rw * qv + qw * rv;

	return Quaternion(vector, scalar);
}

Quaternion Quaternion::IdentityQuaternion()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	return Quaternion(-q.xyz(), q.w);
}

float Quaternion::Norm(const Quaternion& q)
{
	return std::sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
	float norm = Norm(q);
	return Quaternion(q.xyz() / norm, q.w / norm);
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	Quaternion conjugation = Conjugate(q);
	float norm = Norm(q);
	norm *= norm;
	return Quaternion(conjugation.xyz() / norm, conjugation.w / norm);
}

Quaternion Quaternion::MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	return Quaternion(axis * std::sinf(angle / 2.0f), std::cosf(angle / 2.0f));
}

Vector3 Quaternion::RotateVector(const Vector3& vector, const Quaternion& q)
{
	Quaternion result;
	result = q * Quaternion(vector, 0.0f) * Normalize(Inverse(q));
	return Vector3(result.x, result.y, result.z);
}

Matrix4x4 Quaternion::MakeRotateMatrix(const Quaternion& q)
{
	float x = q.x, y = q.y, z = q.z, w = q.w;
	float xx = x * x, yy = y * y, zz = z * z, ww = w * w;
	return {
		ww + xx - yy - zz,2.0f * (x * y + w * z),2.0f * (x * z - w * y),0,
		2.0f * (x * y - w * z) ,ww - xx + yy - zz,2.0f * (y * z + w * x),0,
		2.0f * (x * z + w * y),2.0f * (y * z - w * x),ww - xx - yy + zz,0,
		0,0,0,1
	};
}

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	float dot = Quaternion::Dot(q0, q1);
	Quaternion quat0 = q0;
	if (dot == 0)
	{
		// もう片方の回転を利用
		quat0 = -q0;
		// 内積も反転
		dot = -dot;
	}
	// なす角を求める
	float theta = std::acos(dot);
	// 補間変数
	float scale0 = std::sinf((1 - t) * theta) / std::sinf(theta);
	float scale1 = std::sinf(t * theta) / std::sinf(theta);

	return scale0 * quat0 + scale1 * q1;
}