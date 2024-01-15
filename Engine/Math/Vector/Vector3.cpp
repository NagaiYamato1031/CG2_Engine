#include "Vector3.h"

#include <cmath>
#include <cassert>

#include "../Math.h"

Vector3 Vector3::operator+(const Vector3& obj) const {
	Vector3 result = { this->x + obj.x, this->y + obj.y, this->z + obj.z };
	return result;
}
Vector3 Vector3::operator-(const Vector3& obj) const {
	Vector3 result = { this->x - obj.x,this->y - obj.y, this->z - obj.z };
	return result;
}
Vector3 operator-(const Vector3& obj)
{
	return { -obj.x,-obj.y,-obj.z };
}
Vector3 Vector3::operator*(float scalar) const {
	Vector3 result = { this->x * scalar,this->y * scalar, this->z * scalar };
	return result;
}
Vector3 operator*(float scalar, const Vector3& obj) {
	Vector3 result = { obj.x * scalar, obj.y * scalar, obj.z * scalar };
	return result;
}
Vector3 Vector3::operator*(const Matrix3x3& matrix) const {
	return Multiply(*this, matrix);
}
Vector3 Vector3::operator/(float scalar) const {
	Vector3 result = { this->x / scalar,this->y / scalar, this->z / scalar };
	return result;
}

const Vector3& Vector3::operator+=(const Vector3& obj) {
	*this = *this + obj;
	return *this;
}
const Vector3& Vector3::operator-=(const Vector3& obj) {
	*this = *this - obj;
	return *this;
}
const Vector3& Vector3::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}
const Vector3& Vector3::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}


Vector3 Vector3::Multiply(const Vector3& v, const Matrix3x3& matrix) {
	float temp[3]{ 0, 0, 0 };
	float vf[3]{ v.x, v.y, v.z };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i] += vf[j] * matrix.m[j][i];
		}
	}
	return Vector3{ temp[0], temp[1], temp[2] };
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v2.y * v1.z;
	result.y = v1.z * v2.x - v2.z * v1.x;
	result.z = v1.x * v2.y - v2.x * v1.y;
	return result;
}

// 長さ
float Vector3::Length(const Vector3& v) { return sqrtf(Dot(v, v)); }

// 正規化
Vector3 Vector3::Normalize(const Vector3& v) {
	float length = Length(v);
	Vector3 temp = v;
	if (length != 0) {
		temp.x /= length;
		temp.y /= length;
		temp.z /= length;
	}
	return temp;
}

Vector3 Vector3::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector4 temp = (Vector4{ vector.x, vector.y, vector.z, 1.0f }*matrix);
	assert(temp.w != 0.0f);
	temp.x /= temp.w;
	temp.y /= temp.w;
	temp.z /= temp.w;
	return Vector3{ temp.x, temp.y, temp.z };
}

Vector3 Vector3::TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;
}

Vector3 Vector3::Project(const Vector3& v1, const Vector3& v2) {
	Vector3 normalV2 = Normalize(v2);
	return Dot(v1, normalV2) * normalV2;
}
/*

Vector3 Vector3::CrossestPoint(const Vector3& point, const Segment& segment) {
	return segment.origin + Project(point - segment.origin, segment.diff);
}*/

Vector3 Vector3::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}