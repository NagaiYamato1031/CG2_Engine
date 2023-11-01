#pragma once


#include <vector>
#include <memory>

#include "../Math/Math.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "../Model/Model.h"
#include "../ImGui/ImGuiManager.h"

class IObject
{
protected:

	WorldTransform transformBase_;
	std::vector<WorldTransform> transforms_;

	std::vector<Model*> models_;

	ViewProjection* viewProjection_;

public:

	virtual void Initialize(const std::vector<Model*>& models);
	virtual void Update();
	virtual void Draw();
	virtual void DebugGUI() = 0;

public:

	void UpdateTransform();
	void DrawAllModel();

	void SetParent(WorldTransform* parent) { transformBase_.SetParent(parent); }

	WorldTransform* GetWorldTransform() { return &transformBase_; }

	Vector3 GetWorldPosition() const;

	void SetViewProjection(ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

};