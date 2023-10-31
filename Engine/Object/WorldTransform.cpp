#include "WorldTransform.h"

#include "../Base/DirectXCommon.h"

WorldTransform::WorldTransform() {
	Initialize();
}

void WorldTransform::Initialize() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,0.0f };
	//cBuff_.Reset();
	matWorld_ = Matrix4x4::MakeIdentity4x4();
	parent_ = nullptr;
	parentFlag_ = 0b111;
}

//const Matrix4x4& WorldTransform::GetMatrix()
//{
//	matWorld_ = Matrix4x4::MakeAffineMatrix(scale_, rotate_, translate_);
//
//	if (parent_) {
//		Matrix4x4 matParent = Matrix4x4::MakeIdentity4x4();
//		if (parentFlag_ & 0b100) {
//			matParent = matParent * Matrix4x4::MakeScaleMatrix(parent_->scale_);
//		}if (parentFlag_ & 0b010) {
//			matParent = matParent * Matrix4x4::MakeRotateXYZMatrix(parent_->rotate_);
//		}if (parentFlag_ & 0b001) {
//			matParent = matParent * Matrix4x4::MakeTranslateMatrix(parent_->translate_);
//		}
//		matWorld_ = matParent * matWorld_;
//	}
//
//	return matWorld_;
//}

const Matrix4x4& WorldTransform::GetMatrix()
{
	matWorld_ = Matrix4x4::MakeAffineMatrix(scale_, rotate_, translate_);
	//Matrix4x4 matParent = Matrix4x4::MakeAffineMatrix(wt->scale_, wt->rotate_, wt->translate_);

	if (parent_) {
		Matrix4x4 matParent = Matrix4x4::MakeIdentity4x4();
		if (parentFlag_ != 0b111) {
			WorldTransform* grandParent = parent_->parent_;
			if (grandParent) {
				matParent = grandParent->GetMatrix();
			}
			if (parentFlag_ & 0b100) {
				matParent = matParent * Matrix4x4::MakeScaleMatrix(parent_->scale_);
			}if (parentFlag_ & 0b010) {
				matParent = matParent * Matrix4x4::MakeRotateXYZMatrix(parent_->rotate_);
			}if (parentFlag_ & 0b001) {
				matParent = matParent * Matrix4x4::MakeTranslateMatrix(parent_->translate_);
			}
		}
		else {
			matParent = parent_->GetMatrix();
		}
		matWorld_ =matWorld_ * matParent;
	}

	return matWorld_;
}