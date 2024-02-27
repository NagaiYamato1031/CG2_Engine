#include "Enemy.h"

#include "Resource/Texture/TextureManager.h"

Enemy::Enemy()
{
	model_ = Model::CreateOBJ("userresource/cube", "cube.obj");
	
	model_->SetTexture(TextureManager::GetInstance()->Load("black2x2.png"));

	world_.Initialize();

}

void Enemy::Initialize()
{
	isActive_ = true;
}

void Enemy::Update()
{

	CalcTranslate();
}