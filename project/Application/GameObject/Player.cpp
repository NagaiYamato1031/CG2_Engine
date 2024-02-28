#include "Player.h"

Player::Player()
{
	model_ = Model::CreateOBJ("userresource/cube", "cube.obj");
	world_.Initialize();
	isActive_ = true;
}

void Player::Initialize()
{
	input_ = Input::GetInstance();
}

void Player::Update()
{
	CalcTranslate();
}

void Player::PostUpdate()
{
	prePosition_ = mapPosition_;
}

void Player::MoveUp()
{
	mapPosition_.y++;
}

void Player::MoveDown()
{
	mapPosition_.y--;
}

void Player::MoveLeft()
{
	mapPosition_.x--;
}

void Player::MoveRight()
{
	mapPosition_.x++;
}
