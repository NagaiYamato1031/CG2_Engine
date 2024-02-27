#include "None.h"

#include "Resource/Texture/TextureManager.h"

None::None()
{
	model_ = Model::CreateOBJ("userresource/cube", "cube.obj");
	model_->SetTexture(TextureManager::GetInstance()->Load("circle.png"));
	world_.Initialize();
	isActive_ = true;
}

void None::Initialize()
{
	world_.scale_ = { 1.25f,1.25f,1.0f };
	world_.translate_.z = 2.0f;
}

void None::Update()
{

	CalcTranslate();
}
