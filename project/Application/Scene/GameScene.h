#pragma once

#include "Adapter/Adapter.h"
#include "Scene/BaseScene.h"
#include "Application/GameObject/Player.h"
#include "Application/GameObject/Enemy.h"
#include "Application/GameObject/None.h"

#include <list>
#include <vector>

class GameScene : public BaseScene
{
private:

	const uint32_t kMAPSIZE_ = 9u;


private:

	using Element = GameObject::Element;
	using EnemyList = std::list<std::unique_ptr<Enemy>>;
	using NoneList = std::vector<std::unique_ptr<None>>;
	
	std::vector<std::vector<Element>> map_;
	std::vector<std::vector<Element>> preMap_;

	std::unique_ptr<ViewProjection> view_;

	std::unique_ptr<Player> player_;

	EnemyList enemyList_;

	// グリッド的な
	NoneList noneList_;

	std::unique_ptr<Sprite> spriteMove_;

public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:

	void Escape();

	void UpdateMap();

	Vector2 GetPlayerPosition();
	Vector2 GetPlayerPositionPreview();

	void SetElement(GameObject* obj);
	void MoveElement(GameObject* obj);

	bool CheckCanMove(const Vector2& movePos);
};