#pragma once

#include "Model/Model.h"
#include "Object/WorldTransform.h"
#include "Object/ViewProjection.h"

class GameObject
{
public:

	enum class Element
	{
		None = 0u,
		Player,
		Enemy,
		Destroy,
	};

protected:

	const float kCUBEDISTANCE_ = 2.5f;

	Model* model_ = nullptr;

	Vector2 prePosition_ = { 0.0f,0.0f };
	Vector2 mapPosition_ = { 0.0f,0.0f };

	WorldTransform world_;

	ViewProjection* view_ = nullptr;

	bool isActive_ = false;

public:

	virtual ~GameObject() = default;

	virtual void Initialize();

	virtual void Update();

	virtual void Draw();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveLeft();
	virtual void MoveRight();

	virtual Element GetElement() = 0;

public:

	void SetIsActive(bool flag) { isActive_ = flag; }
	bool GetIsActive()const { return isActive_; }

	void SetPosition(const Vector2& pos) { mapPosition_ = pos; }
	const Vector2& GetPosition() const { return mapPosition_; }
	const Vector2& GetPrePosition() const { return prePosition_; }

	void SetViewProjection(ViewProjection* view) { view_ = view; }



protected:

	void CalcTranslate();
};