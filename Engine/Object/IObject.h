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

	WorldTransform transformBase_;
	std::vector<WorldTransform> transforms_;

	std::vector<Model*> models_;

	ViewProjection* viewProjection_ = nullptr;

	GlobalConfigs* configs_ = nullptr;

public:

	virtual void Initialize(const std::vector<Model*>& models);
	virtual void Update();
	virtual void Draw();
	virtual void DebugGUI() = 0;

	virtual void ApplyConfig();
	virtual void StorageConfig();

public:

	void UpdateTransform();
	void DrawAllModel();

	void SetParent(WorldTransform* parent) { transformBase_.SetParent(parent); }

	WorldTransform* GetWorldTransform() { return &transformBase_; }

	//Vector3 GetWorldPosition() const;

	void SetViewProjection(ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void SetScale(const Vector3& scale) { transformBase_.scale_ = scale; }
	void SetRotate(const Vector3& rotate) { transformBase_.rotate_ = rotate; }
	void SetTranslate(const Vector3& translate) { transformBase_.translate_ = translate; }

};