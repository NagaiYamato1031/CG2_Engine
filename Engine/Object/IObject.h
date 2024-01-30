#pragma once


#include <vector>
#include <memory>

#include "../Math/Math.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "../Model/Model.h"
#include "../ImGui/ImGuiManager.h"
#include "../Configs/GlobalConfigs.h"

/// <summary>
/// ゲーム中に登場するオブジェクト
/// </summary>
class IObject
{
protected:

	std::string name_;

	bool isActive_ = true;

	WorldTransform world_;

	std::unique_ptr<Model> model_;

	ViewProjection* viewProjection_ = nullptr;

	GlobalConfigs* configs_ = nullptr;

public:

	virtual void Initialize(std::string name);
	virtual void Update();
	virtual void Draw();
	virtual void DebugGUI() = 0;

	virtual void ApplyConfig();
	virtual void StorageConfig();

public:

	void UpdateTransform();
	void DrawAllModel();

	void SetParent(WorldTransform* parent) { world_.SetParent(parent); }

	WorldTransform* GetWorldTransform() { return &world_; }

	void SetViewProjection(ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void SetScale(const Vector3& scale) { world_.scale_ = scale; }
	void SetRotate(const Vector3& rotate) { world_.rotate_ = rotate; }
	void SetTranslate(const Vector3& translate) { world_.translate_ = translate; }

	bool GetIsActive() const { return isActive_; }
	void SetIsActive(bool flag) { isActive_ = flag; }
};