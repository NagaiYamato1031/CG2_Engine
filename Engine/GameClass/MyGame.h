#pragma once

#include "../Adapter/Adapter.h"

class MyGame
{
private:

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager* imguiManager_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	std::unique_ptr<CollisionManager> collisionManager_;

	GlobalConfigs* configs_ = nullptr;

	bool endRequest_ = false;

public:

	void Initialize();

	void Finalize();

	void Update();

	void Draw();

	bool IsEndRequest() { return endRequest_; }

private:
	std::unique_ptr<FollowCamera> followCamera_;

	ViewProjection* vp = nullptr;
	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Model> modelPlayerBody_;
	std::unique_ptr<Model> modelPlayerHead_;
	std::unique_ptr<Model> modelPlayerL_arm_;
	std::unique_ptr<Model> modelPlayerR_arm_;
	std::unique_ptr<Model> modelPlayerWeapon_;
	std::unique_ptr<Model> modelGoal_;
	std::unique_ptr<Weapon> weapon_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyHead_;
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<Model> modelFloor0;
	std::unique_ptr<Floor> floor0;
	std::unique_ptr<Model> modelFloor1;
	std::unique_ptr<Floor> floor1;
	std::unique_ptr<Model> modelFloor2;
	std::unique_ptr<Floor> floor2;
	std::vector<Floor*> floors_;
	std::vector<AABB*> aabbs_;
};