#include "BaseCharacter.h"


void BaseCharacter::Initialize(const std::vector<Model*>& models)
{
	models_ = models;
	transformBase_.Initialize();
	transforms_.clear();
}

void BaseCharacter::Update()
{
	transformBase_.GetMatrix();
	for (WorldTransform& wt : transforms_) {
		wt.GetMatrix();
	}
}

void BaseCharacter::Draw()
{
	DrawAllModel();
}

Vector3 BaseCharacter::GetCenterPosition()
{
	return transformBase_.GetWorldPos();
}
