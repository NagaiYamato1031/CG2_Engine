#include "Vector4.h"

#include <cmath>
#include <cassert>

#include "../Math.h"

Vector4 Vector4::operator+(const Vector4& obj) {
	Vector4 result = { this->x + obj.x, this->y + obj.y, this->z + obj.z };
	return result;
}
Vector4 Vector4::operator-(const Vector4& obj) {
	Vector4 result = { this->x - obj.x,this->y - obj.y, this->z + obj.z };
	return result;
}
Vector4 Vector4::operator*(float scalar) {
	Vector4 result = { this->x * scalar,this->y * scalar, this->z * scalar };
	return result;
}
Vector4 operator*(float scalar, const Vector4& obj) {
	Vector4 result = { obj.x * scalar, obj.y * scalar, obj.z * scalar };
	return result;
}
Vector4 Vector4::operator*(const Matrix4x4& matrix) {
	return Multiply(*this, matrix);
}
Vector4 Vector4::operator/(float scalar) {
	Vector4 result = { this->x / scalar,this->y / scalar, this->z / scalar };
	return result;
}

const Vector4& Vector4::operator+=(const Vector4& obj) {
	*this = *this + obj;
	return *this;
}
const Vector4& Vector4::operator-=(const Vector4& obj) {
	*this = *this - obj;
	return *this;
}
const Vector4& Vector4::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}
const Vector4& Vector4::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}


Vector4 Vector4::Multiply(const Vector4& v, const Matrix4x4& matrix) {
	float temp[4]{ 0, 0, 0, 0 };
	float vf[4]{ v.x, v.y, v.z,v.w };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i] += vf[j] * matrix.m[j][i];
		}
	}
	return Vector4{ temp[0], temp[1], temp[2],temp[3] };
}

float Vector4::Dot(const Vector4& v1, const Vector4& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

//Vector4 Vector4::Cross(const Vector4& v1, const Vector4& v2) {
//	Vector4 result;
//	result.x = v1.y * v2.z - v2.y * v1.z;
//	result.y = v1.z * v2.x - v2.z * v1.x;
//	result.z = v1.x * v2.y - v2.x * v1.y;
//	return result;
//}

// 長さ
float Vector4::Length(const Vector4& v) { return sqrtf(Dot(v, v)); }

// 正規化
Vector4 Vector4::Normalize(const Vector4& v) {
	float length = Length(v);
	Vector4 temp = v;
	if (length != 0) {
		temp.x /= length;
		temp.y /= length;
		temp.z /= length;
		temp.w /= length;
	}
	return temp;
}
//
//Vector4 Vector4::Transform(const Vector4& vector, const Matrix4x4& matrix) {
//	Vector4 temp = (Vector4{ vector.x, vector.y, vector.z, 1.0f }*matrix);
//	assert(temp.w != 0.0f);
//	temp.x /= temp.w;
//	temp.y /= temp.w;
//	temp.z /= temp.w;
//	return Vector4{ temp.x, temp.y, temp.z };
//}
//
//Vector4 Vector4::TransformNormal(const Vector4& v, const Matrix4x4& m) {
//	Vector4 result{
//		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
//		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
//		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
//	};
//	return result;
//}