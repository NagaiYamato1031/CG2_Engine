#pragma once

#include "../IObject.h"

class BaseCharacter : public IObject
{
public:

	virtual void Initialize(const std::vector<Model*>& models) override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DebugGUI() override = 0;

protected:
	

};