#pragma once

#include "Scenes.h"

class IScene
{
protected:

	static Scene sSceneNo_;

public:

	// 初期化
	virtual void Initialize() = 0;
	// 再読み込み
	virtual void Reset() {};
	// 更新
	virtual void Update() = 0;
	// モデル描画
	virtual void DrawModel() {};
	// スプライト描画
	virtual void DrawSprite() {};

	// デバッグ表示
	virtual void Debug() {}

public:

	Scene GetSceneNo() const { return sSceneNo_; }

};