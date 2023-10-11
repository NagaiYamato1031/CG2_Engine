#include "Matrix3x3.h"

#include <cmath>
#include <cassert>

#include "../Math.h"

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& obj) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = this->m[i][j] + obj.m[i][j];
		}
	}
	return result;
}
Matrix3x3 Matrix3x3::operator-(const Matrix3x3& obj) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = this->m[i][j] - obj.m[i][j];
		}
	}
	return result;
}
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& obj) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = this->m[i][0] * obj.m[0][j] + this->m[i][1] * obj.m[1][j] + this->m[i][2] * obj.m[2][j];
		}
	}
	return result;
}
Matrix3x3 Matrix3x3::operator*(float scalar) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = this->m[i][j] * scalar;
		}
	}
	return result;
}

Matrix3x3 operator*(float scalar, const Matrix3x3& obj) {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = obj.m[i][j] * scalar;
		}
	}
	return result;
}

const Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& obj) {
	*this = *this + obj;
	return *this;
}
const Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& obj) {
	*this = *this - obj;
	return *this;
}
const Matrix3x3& Matrix3x3::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}


Matrix3x3 Matrix3x3::Add(const Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 + m2;
}

Matrix3x3 Matrix3x3::Subtract(const Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 - m2;
}

Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& m1, const Matrix3x3& m2) {
	return m1 * m2;
}

/*


Matrix3x3 Matrix3x3::Inverse(const Matrix3x3& matrix) {
	float det;
	det = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
		matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]

		- matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]

		- matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
		matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]

		+ matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]

		+ matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
		matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] +
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]

		- matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
		matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]

		- matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
		matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]

		+ matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
		matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0];

	float det11 = 1 / det *
		(+matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
			matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
			matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
			matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
			matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]);
	float det12 = 1 / det *
		(-matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] -
			matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1] -
			matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1] +
			matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]);
	float det13 = 1 / det *
		(+matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
			matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1] +
			matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1] -
			matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]);
	float det14 = 1 / det *
		(-matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] -
			matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] +
			matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] +
			matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] +
			matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]);

	float det21 = 1 / det *
		(-matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
			matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
			matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] +
			matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] +
			matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
			matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]);

	float det22 = 1 / det *
		(+matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0] +
			matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2] -
			matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0] -
			matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]);

	float det23 = 1 / det *
		(-matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0] -
			matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2] +
			matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0] +
			matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3] +
			matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]);

	float det24 = 1 / det *
		(+matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
			matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] +
			matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] -
			matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] -
			matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] -
			matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]);

	float det31 = 1 / det *
		(+matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
			matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
			matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
			matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]);

	float det32 = 1 / det *
		(-matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0] -
			matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1] +
			matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0] +
			matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3] +
			matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]);

	float det33 = 1 / det *
		(+matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
			matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0] +
			matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1] -
			matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0] -
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]);

	float det34 = 1 / det *
		(-matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] -
			matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] -
			matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] +
			matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] +
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] +
			matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]);

	float det41 = 1 / det *
		(-matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] -
			matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] -
			matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] +
			matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
			matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] +
			matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]);

	float det42 = 1 / det *
		(+matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0] +
			matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1] -
			matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0] -
			matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2] -
			matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]);

	float det43 = 1 / det *
		(-matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0] -
			matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1] +
			matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0] +
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2] +
			matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]);

	float det44 = 1 / det *
		(+matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
			matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
			matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
			matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
			matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	Matrix3x3 result = { det11, det12, det13, det14, det21, det22, det23, det24,
						det31, det32, det33, det34, det41, det42, det43, det44 };
	return result;
}

Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& matrix) {
	Matrix3x3 temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp.m[i][j] = matrix.m[j][i];
		}
	}
	return temp;
}

Matrix3x3 Matrix3x3::MakeIdentity3x3() {
	return Matrix3x3{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

Matrix3x3 Matrix3x3::MakeTranslateMatrix(const Vector3& translate) {
	Matrix3x3 translateMatrix_ = { 1, 0, 0, 0, 0,           1,           0,           0,
								  0, 0, 1, 0, translate.x, translate.y, translate.z, 1 };
	return translateMatrix_;
}

Matrix3x3 Matrix3x3::MakeScaleMatrix(const Vector3& scale) {
	Matrix3x3 scaleMatrix_ = { scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1 };
	return scaleMatrix_;
}

Matrix3x3 Matrix3x3::MakeRotateXMatrix(float radian) {
	Matrix3x3 rotX_ = {
		1,0,0,0,
		0, std::cosf(radian), std::sinf(radian), 0,
		0, -std::sinf(radian), std::cosf(radian), 0,
		0, 0, 0, 1
	};
	return rotX_;
}

Matrix3x3 Matrix3x3::MakeRotateYMatrix(float radian) {
	Matrix3x3 rotY_ = {
		std::cosf(radian), 0, -std::sinf(radian), 0,
		0, 1, 0, 0,
		std::sinf(radian), 0, std::cosf(radian),  0,
		0, 0, 0, 1
	};
	return rotY_;
}

Matrix3x3 Matrix3x3::MakeRotateZMatrix(float radian) {
	Matrix3x3 rotZ_ = {
		std::cosf(radian),std::sinf(radian),0,0,
		-std::sinf(radian),std::cosf(radian),0,0,
		0,0,1,0,
		0,0,0,1
	};
	return rotZ_;
}

Matrix3x3 Matrix3x3::MakeRotateXYZMatrix(const Vector3& radian) {
	Matrix3x3 rotX_ = MakeRotateXMatrix(radian.x);
	Matrix3x3 rotY_ = MakeRotateYMatrix(radian.y);
	Matrix3x3 rotZ_ = MakeRotateZMatrix(radian.z);
	return Multiply(Multiply(rotX_, rotY_), rotZ_);
}

Matrix3x3
Matrix3x3::MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {

	Matrix3x3 scaleMatrix_ = MakeScaleMatrix(scale);

	Matrix3x3 rotateMatrix_ = MakeRotateXYZMatrix(rot);

	Matrix3x3 translateMatrix_ = MakeTranslateMatrix(translate);

	return Multiply(Multiply(scaleMatrix_, rotateMatrix_), translateMatrix_);
}

Matrix3x3 Matrix3x3::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix3x3 result{
		1 / aspectRatio * (1 / std::tanf(fovY / 2)),0,0,0,
		0,(1 / std::tanf(fovY / 2)),0,0,
		0,0,farClip / (farClip - nearClip),1,
		0,0,(-nearClip * farClip) / (farClip - nearClip),0.0f
	};
	return result;
}

Matrix3x3 Matrix3x3::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix3x3 result{
		2 / (right - left),0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / (farClip - nearClip),0,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};
	return result;
}

Matrix3x3 Matrix3x3::MakeOrthographicMatrix(const Vector2& leftTop, const Vector2& rightBottom, const Vector2& nearFar) {
	return MakeOrthographicMatrix(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y, nearFar.x, nearFar.y);
}

Matrix3x3 Matrix3x3::MakeViewportMatrix(float left, float top, float width, float height, float minD = 0, float maxD = 1) {
	assert(minD <= maxD);
	Matrix3x3 result{
		width / 2.0f,0,0,0,
		0,-height / 2.0f,0,0,
		0,0,maxD - minD,0,
		left + width / 2.0f,top + height / 2.0f, minD,1
	};
	return result;
}
Matrix3x3 Matrix3x3::MakeViewportMatrix(const Vector2& leftTop, const Vector2& size, const Vector2& depth = { 0,1 }) {
	return MakeViewportMatrix(leftTop.x, leftTop.y, size.x, size.y, depth.x, depth.y);
}
Matrix3x3 Matrix3x3::MakeViewportMatrix(const Vector4& info, const Vector2& depth = { 0,1 }) {
	return MakeViewportMatrix(info.x, info.y, info.z, info.w, depth.x, depth.y);
}
*/