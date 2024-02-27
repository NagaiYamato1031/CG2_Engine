#pragma once

#include "GameObject.h"

class None : public GameObject
{
private:


public:

	None();

	void Initialize() override;

	void Update() override;

	Element GetElement() override { return Element::None; }

};