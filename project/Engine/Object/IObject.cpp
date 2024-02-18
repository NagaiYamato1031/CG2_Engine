#include "IObject.h"


void IObject::Initialize(const std::vector<Model*>& models)
{
	models_ = models;
	transformBase_.Initialize();
	transforms_.clear();
}

void IObject::Update()
{
	UpdateTransform();
}

void IObject::Draw()
{
	DrawAllModel();
}

void IObject::ApplyConfig()
{
}

void IObject::StorageConfig()
{
}

void IObject::UpdateTransform()
{
	transformBase_.GetMatrix();
	for (WorldTransform& wt : transforms_) {
		wt.GetMatrix();
	}
}

void IObject::DrawAllModel()
{
	for (size_t i = 0; i < transforms_.size(); i++)
	{
		models_[i]->Draw(&transforms_[i], viewProjection_);
	}
}
//
//Vector3 IObject::GetWorldPosition() const
//{
//	return Vector3();
//}
