#pragma once

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

	// オブジェクトのタグ
	std::string tag_;
	
	// 起動状態か
	// 多分消すやつ
	bool isActive_ = true;

	// 描画するか
	bool isDraw_ = true;

	// どのカメラを参照するか
	ViewProjection* viewProjection_ = nullptr;

	WorldTransform world_;

	// 外部保存用
	// クラス内で保存機構を作ってもいい
	GlobalConfigs* configs_ = nullptr;

public:

	virtual void Initialize();
	virtual void Initialize(std::string tag);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DebugGUI() = 0;

	virtual void ApplyConfig();
	virtual void StorageConfig();

public:

	void SetParent(WorldTransform* parent) { world_.SetParent(parent); }

	WorldTransform* GetWorldTransform() { return &world_; }

	void SetViewProjection(ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void SetScale(const Vector3& scale) { world_.scale_ = scale; }
	void SetRotate(const Vector3& rotate) { world_.rotate_ = rotate; }
	void SetTranslate(const Vector3& translate) { world_.translate_ = translate; }

	const std::string& GetTag() const { return tag_; }

	bool GetIsActive() const { return isActive_; }
	void SetIsActive(bool flag) { isActive_ = flag; }
	bool GetIsDraw() const { return isDraw_; }
	void SetIsDraw(bool flag) { isDraw_ = flag; }
};