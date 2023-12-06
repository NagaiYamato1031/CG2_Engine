#pragma once

#include "Framework.h"

class MyGame : public Framework
{
public:

	~MyGame() override;

	void Initialize() override;
	void Reset();

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:
	std::unique_ptr<Camera> camera_;

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
	std::vector<std::unique_ptr<Model>> modelEnemyBodys_;
	std::vector<std::unique_ptr<Model>> modelEnemyHeads_;
	std::vector<std::unique_ptr<Enemy>> enemys_;
	std::unique_ptr<Model> modelFloor0;
	std::unique_ptr<Floor> floor0;
	std::unique_ptr<Model> modelFloor1;
	std::unique_ptr<Floor> floor1;
	std::unique_ptr<Model> modelFloor2;
	std::unique_ptr<Floor> floor2;
	std::vector<Floor*> floors_;
	std::vector<AABB*> aabbs_;
};