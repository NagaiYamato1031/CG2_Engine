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

Quaternion Quaternion::operator*(const Quaternion& obj) const
{
	return Multiply(*this, obj);
}

Vector3 Quaternion::GetVector()const
{
	return Vector3(this->x, this->y, this->z);
}

float Quaternion::GetScalar()const
{
	return this->w;
}

Quaternion Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2)
{
	Vector3 qv = q1.GetVector();
	float qw = q1.GetScalar();
	Vector3 rv = q2.GetVector();
	float rw = q2.GetScalar();

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
	return Quaternion(-q.GetVector(), q.GetScalar());
}

float Quaternion::Norm(const Quaternion& q)
{
	return std::sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
	float norm = Norm(q);
	return Quaternion(q.GetVector() / norm, q.GetScalar() / norm);
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	Quaternion conjugation = Conjugate(q);
	float norm = Norm(q);
	norm *= norm;
	return Quaternion(conjugation.GetVector() / norm, conjugation.GetScalar() / norm);
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

