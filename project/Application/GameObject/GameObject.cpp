#include "GameObject.h"

void GameObject::Initialize()
{
	world_.Initialize();
	isActive_ = true;
}

void GameObject::Update()
{
	CalcTranslate();
}

void GameObject::Draw()
{
	if (model_)
	{
		model_->Draw(&world_, view_);
	}
}

void GameObject::MoveUp()
{
	mapPosition_.y++;
}

void GameObject::MoveDown()
{
	mapPosition_.y--;
}

void GameObject::MoveLeft()
{
	mapPosition_.x--;
}

void GameObject::MoveRight()
{
	mapPosition_.x++;
}

void GameObject::CalcTranslate()
{
	Vector3 pos = { mapPosition_.x,mapPosition_.y,0.0f };
	pos *= kCUBEDISTANCE_;
	pos.z = world_.translate_.z;
	world_.translate_ = pos;
}
