#include "Player.h"

void Player::Initialize()
{
	IObject::Initialize("player");

	model_.reset(Model::CreateOBJ("Resources", "fence"));
}

void Player::Update()
{
}

void Player::Draw()
{
	model_->Draw(&world_, viewProjection_);
}

void Player::DebugGUI()
{
}
