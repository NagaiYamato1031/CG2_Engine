#pragma once

#include "../../IObject.h"

/// <summary>
/// 天球
/// </summary>
class Skydome final : public IObject{
public:
	/// <summary>
	///  初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	///	更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	void DebugGUI() override;

private: // メンバ変数
};