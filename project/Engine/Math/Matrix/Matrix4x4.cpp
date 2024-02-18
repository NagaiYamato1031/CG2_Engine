#include "Matrix4x4.h"

#include <cmath>
#include <cassert>

#include "../Math.h"

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& obj) const
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = this->m[i][j] + obj.m[i][j];
		}
	}
	return result;
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& obj) const
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = this->m[i][j] - obj.m[i][j];
		}
	}
	return result;
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& obj) const
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = this->m[i][0] * obj.m[0][j] + this->m[i][1] * obj.m[1][j] + this->m[i][2] * obj.m[2][j] + this->m[i][3] * obj.m[3][j];
		}
	}
	return result;
}
Matrix4x4 Matrix4x4::operator*(float scalar) const
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = this->m[i][j] * scalar;
		}
	}
	return result;
}

Matrix4x4 operator*(float scalar, const Matrix4x4& obj)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = obj.m[i][j] * scalar;
		}
	}
	return result;
}

const Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& obj)
{
	*this = *this + obj;
	return *this;
}
const Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& obj)
{
	*this = *this - obj;
	return *this;
}
const Matrix4x4& Matrix4x4::operator*=(float scalar)
{
	*this = *this * scalar;
	return *this;
}


Matrix4x4 Matrix4x4::Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return m1 + m2;
}

Matrix4x4 Matrix4x4::Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return m1 - m2;
}

Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	return m1 * m2;
}


Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& matrix)
{
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

	Matrix4x4 result = { det11, det12, det13, det14, det21, det22, det23, det24,
						det31, det32, det33, det34, det41, det42, det43, det44 };
	return result;
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& matrix)
{
	Matrix4x4 temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp.m[i][j] = matrix.m[j][i];
		}
	}
	return temp;
}

Matrix4x4 Matrix4x4::MakeIdentity4x4()
{
	return Matrix4x4{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

Matrix4x4 Matrix4x4::MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 translateMatrix_ =
	{ 1, 0, 0, 0,
	  0, 1, 0, 0,
	  0, 0, 1, 0,
	translate.x, translate.y, translate.z, 1 };
	return translateMatrix_;
}

Matrix4x4 Matrix4x4::MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 scaleMatrix_ = { scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1 };
	return scaleMatrix_;
}

Matrix4x4 Matrix4x4::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotX_ = { 1,
					   0,
					   0,
					   0,
					   0,
					   std::cosf(radian),
					   std::sinf(radian),
					   0,
					   0,
					   -std::sinf(radian),
					   std::cosf(radian),
					   0,
					   0,
					   0,
					   0,
					   1 };
	return rotX_;
}

Matrix4x4 Matrix4x4::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotY_ = { std::cosf(radian), 0, -std::sinf(radian), 0, 0, 1, 0, 0,
					   std::sinf(radian), 0, std::cosf(radian),  0, 0, 0, 0, 1 };
	return rotY_;
}

Matrix4x4 Matrix4x4::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotZ_ = {
		std::cosf(radian),
		std::sinf(radian),
		0,
		0,
		-std::sinf(radian),
		std::cosf(radian),
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		1 };
	return rotZ_;
}

Matrix4x4 Matrix4x4::MakeRotateXYZMatrix(const Vector3& radian)
{
	Matrix4x4 rotX_ = MakeRotateXMatrix(radian.x);
	Matrix4x4 rotY_ = MakeRotateYMatrix(radian.y);
	Matrix4x4 rotZ_ = MakeRotateZMatrix(radian.z);
	return Multiply(Multiply(rotX_, rotY_), rotZ_);
}

Matrix4x4 Matrix4x4::MakeRotateAxisMatrix(const Vector3& axis, float angle)
{
	Matrix4x4 result = MakeIdentity4x4();

	float cosTheta = std::cosf(angle);
	Matrix3x3 matS = { cosTheta,0,0,0,cosTheta,0,0,0,cosTheta };

	Matrix3x3 matP = {
		axis.x * axis.x,axis.x * axis.y,axis.x * axis.z,
		axis.x * axis.y,axis.y * axis.y,axis.y * axis.z,
		axis.x * axis.z,axis.y * axis.z,axis.z * axis.z
	};
	matP = (1 - cosTheta) * matP;

	Matrix3x3 matC = {
		0,-axis.z,axis.y,
		axis.z,0,-axis.x,
		-axis.y,axis.x,0
	};
	matC = -std::sinf(angle) * matC;

	Matrix3x3 matR = matS + matP + matC;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{

			result.m[i][j] = matR.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Matrix4x4::DirectionToDirection(const Vector3& from, const Vector3& to)
{
	Vector3 axis = Vector3::Normalize(Vector3::Cross(from, to));
	Matrix4x4 result = MakeIdentity4x4();

	float cosTheta = Vector3::Dot(from, to);

	if (cosTheta == -1.0f)
	{
		axis = (from.x != 0.0f || from.y != 0.0f) ? Vector3::Normalize({ from.y, -from.x, 0.0f }) : (from.x != 0.0f || from.z != 0.0f) ? Vector3::Normalize({ from.z, 0.0f, -from.x }) : from;
	}

	Matrix3x3 matS = { cosTheta,0,0,0,cosTheta,0,0,0,cosTheta };

	Matrix3x3 matP = {
		axis.x * axis.x,axis.x * axis.y,axis.x * axis.z,
		axis.x * axis.y,axis.y * axis.y,axis.y * axis.z,
		axis.x * axis.z,axis.y * axis.z,axis.z * axis.z
	};
	matP = (1 - cosTheta) * matP;

	Matrix3x3 matC = {
		0,-axis.z,axis.y,
		axis.z,0,-axis.x,
		-axis.y,axis.x,0
	};
	matC = -Vector3::Length(Vector3::Cross(from, to)) * matC;

	Matrix3x3 matR = matS + matP + matC;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{

			result.m[i][j] = matR.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Matrix4x4::MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate)
{

	Matrix4x4 scaleMatrix_ = MakeScaleMatrix(scale);

	Matrix4x4 rotateMatrix_ = MakeRotateXYZMatrix(rot);

	Matrix4x4 translateMatrix_ = MakeTranslateMatrix(translate);

	return Multiply(Multiply(scaleMatrix_, rotateMatrix_), translateMatrix_);
}

Matrix4x4 Matrix4x4::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result{
		1 / aspectRatio * (1 / std::tanf(fovY / 2)),0,0,0,
		0,(1 / std::tanf(fovY / 2)),0,0,
		0,0,farClip / (farClip - nearClip),1,
		0,0,(-nearClip * farClip) / (farClip - nearClip),0.0f
	};
	return result;
}

Matrix4x4 Matrix4x4::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result{
		2 / (right - left),0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / (farClip - nearClip),0,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};
	return result;
}

Matrix4x4 Matrix4x4::MakeOrthographicMatrix(const Vector2& leftTop, const Vector2& rightBottom, const Vector2& nearFar)
{
	return MakeOrthographicMatrix(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y, nearFar.x, nearFar.y);
}

Matrix4x4 Matrix4x4::MakeViewportMatrix(float left, float top, float width, float height, float minD = 0, float maxD = 1)
{
	assert(minD <= maxD);
	Matrix4x4 result{
		width / 2.0f,0,0,0,
		0,-height / 2.0f,0,0,
		0,0,maxD - minD,0,
		left + width / 2.0f,top + height / 2.0f, minD,1
	};
	return result;
}
Matrix4x4 Matrix4x4::MakeViewportMatrix(const Vector2& leftTop, const Vector2& size, const Vector2& depth = { 0,1 })
{
	return MakeViewportMatrix(leftTop.x, leftTop.y, size.x, size.y, depth.x, depth.y);
}
Matrix4x4 Matrix4x4::MakeViewportMatrix(const Vector4& info, const Vector2& depth = { 0,1 })
{
	return MakeViewportMatrix(info.x, info.y, info.z, info.w, depth.x, depth.y);
}