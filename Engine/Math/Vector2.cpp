#include "Vector2.h"

#include <cmath>
#include <cassert>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

Vector2 Vector2::operator+(const Vector2& obj) const {
	Vector2 result = { this->x + obj.x, this->y + obj.y };
	return result;
}
Vector2 Vector2::operator-(const Vector2& obj) const {
	Vector2 result = { this->x - obj.x,this->y - obj.y };
	return result;
}
Vector2 Vector2::operator*(float scalar) {
	Vector2 result = { this->x * scalar,this->y * scalar };
	return result;
}
Vector2 operator*(float scalar, const Vector2& obj) {
	Vector2 result = { obj.x * scalar,obj.y * scalar };
	return result;
}
Vector2 Vector2::operator/(float scalar) const {
	Vector2 result = { this->x / scalar,this->y / scalar };
	return result;
}

const Vector2& Vector2::operator+=(const Vector2& obj) {
	*this = *this + obj;
	return *this;
}
const Vector2& Vector2::operator-=(const Vector2& obj) {
	*this = *this - obj;
	return *this;
}
const Vector2& Vector2::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}
const Vector2& Vector2::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

// 長さ
float Vector2::Length(const Vector2& v) { return sqrtf(Dot(v, v)); }

// 正規化
Vector2 Vector2::Normalize(const Vector2& v) {
	float length = Length(v);
	Vector2 temp = v;
	if (length != 0) {
		temp.x /= length;
		temp.y /= length;
	}
	return temp;
}

Vector2 Vector2::Transform(const Vector2& vector, const Matrix3x3& matrix) {
	Vector3 temp = (Vector3{ vector.x, vector.y, 1.0f } *matrix);
	assert(temp.z != 0.0f);
	temp.x /= temp.z;
	temp.y /= temp.z;
	return Vector2{ temp.x, temp.y };
}