#include "IObject.h"


void IObject::Initialize()
{
	Initialize("obj");
}

void IObject::Initialize(std::string tag)
{
	tag_ = tag;
	configs_ = GlobalConfigs::GetInstance();
	isActive_ = true;
	isDraw_ = true;
	viewProjection_ = nullptr;
}

//void IObject::Update()
//{
//	UpdateTransform();
//}
//
//void IObject::Draw()
//{
//	DrawAllModel();
//}

void IObject::ApplyConfig()
{
}

void IObject::StorageConfig()
{
}
