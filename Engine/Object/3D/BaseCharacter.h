#pragma once

#include "../IObject.h"
#include "../../Collider/Collider.h"

class BaseCharacter : public IObject , public Collider
{
public:

	virtual void Initialize(const std::vector<Model*>& models) override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DebugGUI() override = 0;

	virtual Vector3 GetCenterPosition() override;

protected:


};