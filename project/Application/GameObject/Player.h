#pragma once

#include "GameObject.h"

#include "Input/Input.h"

class Player : public GameObject
{
private:

	Input* input_ = nullptr;

public:

	Player();

	void Initialize() override;

	void Update() override;

	void MoveUp() override;
	void MoveDown() override;
	void MoveLeft() override;
	void MoveRight() override;

	Element GetElement() override { return Element::Player; }

};