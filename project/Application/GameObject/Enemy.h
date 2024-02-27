#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
private:


public:

	Enemy();

	void Initialize() override;

	void Update() override;

	Element GetElement() override { return Element::Enemy; }
};