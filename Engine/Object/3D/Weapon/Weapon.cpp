#include "Weapon.h"

void Weapon::Initialize(const std::vector<Model*>& models)
{
	models_ = models;
	transformBase_.Initialize();
	transforms_.clear();
}

void Weapon::Initialize(const std::vector<Model*>& models, WorldTransform* wt)
{
	models_ = models;
	transformBase_.Initialize();
	transformBase_.SetParent(wt);
	transforms_.clear();
	isActive_ = false;
	isDraw_ = false;
}

void Weapon::Reset()
{
	transformBase_.rotate_ = { 0.0f,0.0f,0.0f };
	//isActive_ = true;
	isDraw_ = true;
}

void Weapon::Update()
{
	DebugGUI();
}

void Weapon::Update(Vector3 theta)
{
	transformBase_.rotate_ = theta;
}

void Weapon::Draw()
{
	if (isDraw_)
		models_[0]->Draw(&transformBase_, viewProjection_);
}

void Weapon::ApplyConfig()
{
}

void Weapon::StorageConfig()
{
}

void Weapon::DebugGUI()
{
#ifdef _DEBUG

	ImGui::Begin("Weapon");

	ImGui::DragFloat3("translate", &transformBase_.translate_.x, 0.01f);
	Vector3 pos = transformBase_.GetWorldPos();
	ImGui::DragFloat3("worldPos", &pos.x, 0.01f);


	ImGui::End();

#endif // _DEBUG

}

Vector3 Weapon::GetCenterPosition()
{
	Vector3 center{ transformBase_.GetWorldPos()};
	Vector3 offset{ 0.0f,1.0f,3.0f };

	Matrix4x4 matRotate = transformBase_.GetMatrix(0b010);

	offset = Vector3::TransformNormal(offset, matRotate);

	return center + offset;
}

void Weapon::OnCollisionEnter()
{
}

void Weapon::OnCollision()
{
}

void Weapon::OnCollisionExit()
{
}
