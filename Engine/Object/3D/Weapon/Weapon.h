#pragma once

#include "../../IObject.h"
#include "../../../Collider/Collider.h"

class Weapon final : public IObject, public Collider
{
private:

	bool isDraw_ = false;

	/// <summary>
	/// オーバーライド
	/// </summary>
public:

	void Initialize(const std::vector<Model*>& models) override;
	void Initialize(const std::vector<Model*>& models, WorldTransform* wt);

	void Reset();
	void Update() override;
	void Update(Vector3 theta);

	void Draw() override;

	void ApplyConfig() override;
	void StorageConfig() override;

	void DebugGUI() override;

	Vector3 GetCenterPosition() override;

	void OnCollisionEnter() override;
	void OnCollision() override;
	void OnCollisionExit() override;

	void SetIsDraw(bool flag) { isDraw_ = flag; }

};