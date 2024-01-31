#pragma once

#include "../IObject.h"

class Player : public IObject
{
private:

	std::unique_ptr<Model> model_;

public:

	void Initialize();
	void Update() override;
	void Draw() override;
	void DebugGUI() override;
};