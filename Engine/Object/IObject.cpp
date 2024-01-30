#include "IObject.h"


void IObject::Initialize(std::string name)
{
	name_ = name;
	world_.Initialize();
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
	world_.GetMatrix();
}

void IObject::DrawAllModel()
{
	model_->Draw(&world_, viewProjection_);
}