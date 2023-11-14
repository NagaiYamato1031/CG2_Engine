#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/ImGui/ImGuiManager.h"
#include "Engine/Resource/Texture/TextureManager.h"
#include "Engine/Model/Model.h"
#include "Engine/Collider/CollisionManager.h"
#include "Engine/Object/ViewProjection.h"
#include "Engine/Configs/GlobalConfigs.h"
#include "Engine/Object/3D/3dObjectList.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager* imguiManager_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	GlobalConfigs* configs_ = nullptr;


	winApp_ = WinApp::GetInstance();
	winApp_->Initialize("Engine", 1280, 720);

	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize(winApp_);

	input_ = Input::GetInstance();
	input_->Initialize(winApp_);

	imguiManager_ = ImGuiManager::GetInstance();
	imguiManager_->Initialize(winApp_, dxCommon_);

	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	Model::StaticInitialize(dxCommon_);

	std::unique_ptr<CollisionManager> collisionManager_;
	collisionManager_.reset(new CollisionManager);

	configs_ = GlobalConfigs::GetInstance();
	configs_->LoadFiles();

	/*////////////////////
	//	ゲームで使う変数	//
	//------------------*/

	std::unique_ptr<FollowCamera> followCamera_;
	followCamera_.reset(new FollowCamera);
	followCamera_->Initialize();

	ViewProjection* vp = followCamera_->GetViewProjection();

	std::unique_ptr<Model> modelSkydome_;
	modelSkydome_.reset(Model::CreateOBJ("resources/skydome", "skydome.obj"));

	std::unique_ptr<Skydome> skydome_;
	skydome_.reset(new Skydome());
	skydome_->Initialize(modelSkydome_.get());

	std::unique_ptr<Model> modelPlayerBody_;
	std::unique_ptr<Model> modelPlayerHead_;
	std::unique_ptr<Model> modelPlayerL_arm_;
	std::unique_ptr<Model> modelPlayerR_arm_;
	std::unique_ptr<Model> modelPlayerWeapon_;
	std::unique_ptr<Model> modelGoal_;

	modelPlayerBody_.reset(Model::CreateOBJ("resources/player", "player_Body.obj"));
	modelPlayerHead_.reset(Model::CreateOBJ("resources/player", "player_Head.obj"));
	modelPlayerL_arm_.reset(Model::CreateOBJ("resources/player", "player_L_arm.obj"));
	modelPlayerR_arm_.reset(Model::CreateOBJ("resources/player", "player_R_arm.obj"));
	modelPlayerWeapon_.reset(Model::CreateOBJ("resources/player", "player_Weapon.obj"));

	modelGoal_.reset(Model::CreateOBJ("resources/player", "goal.obj"));

	std::vector<Model*> playerModels = {
		modelPlayerBody_.get(),modelPlayerHead_.get(),
		modelPlayerL_arm_.get(),modelPlayerR_arm_.get(),
		modelPlayerWeapon_.get(),modelGoal_.get()
	};

	std::unique_ptr<Weapon> weapon_;
	weapon_.reset(new Weapon);

	std::unique_ptr<Player> player_;
	player_.reset(new Player);
	player_->Initialize(playerModels);

	player_->SetViewProjection(vp);
	followCamera_->SetTarget(player_->GetWorldTransform());

	player_->SetWeapon(weapon_.get());
	weapon_->SetViewProjection(vp);

	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyHead_;

	modelEnemyBody_.reset(Model::CreateOBJ("resources/enemy", "enemy_Body.obj"));
	modelEnemyHead_.reset(Model::CreateOBJ("resources/enemy", "enemy_Head.obj"));

	std::vector<Model*> enemyModels = {
		modelEnemyBody_.get(),modelEnemyHead_.get(),
	};

	std::unique_ptr<Enemy> enemy_;
	enemy_.reset(new Enemy);
	enemy_->Initialize(enemyModels);

	enemy_->SetViewProjection(vp);

	player_->SetEnemy(enemy_.get());

	std::unique_ptr<Model> modelFloor0;
	modelFloor0.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	std::unique_ptr<Floor> floor0;
	floor0.reset(new Floor);
	floor0->Initialize(modelFloor0.get(), false);
	floor0->start_ = { 0.0f,0.0f,0.0f };
	floor0->end_ = { 0.0f,0.0f,0.0f };
	floor0->SetScale({ 25.0f,1.0f,25.0f });
	floor0->isMove_ = false;

	std::unique_ptr<Model> modelFloor1;
	modelFloor1.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	std::unique_ptr<Floor> floor1;
	floor1.reset(new Floor);
	floor1->Initialize(modelFloor1.get(), false);
	floor1->start_ = { 18.0f,4.0f,20.0f };
	floor1->end_ = { 4.0f,7.0f,57.0f };
	floor1->isMove_ = true;

	std::unique_ptr<Model> modelFloor2;
	modelFloor2.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	std::unique_ptr<Floor> floor2;
	floor2.reset(new Floor);
	floor2->Initialize(modelFloor2.get(), false);
	floor2->start_ = { -20.0f,10.0f,60.0f };
	floor2->end_ = { 0.0f,0.0f,0.0f };
	floor2->isMove_ = false;



	// 床をまとめる
	std::vector<Floor*> floors_;
	floors_.push_back(floor0.get());
	floors_.push_back(floor1.get());
	floors_.push_back(floor2.get());
	std::vector<AABB*> aabbs_;

	//aabbs_.push_back(enemy_->GetAABB());

	for (Floor*& floor : floors_) {
		floor->SetViewProjection(vp);
		aabbs_.push_back(&floor->aabb);
	}

	uint32_t textureWhite_ = TextureManager::Load("white2x2.png");
	floor1->SetTexture(textureWhite_);
	floor2->SetTexture(textureWhite_);

	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


	while (!winApp_->ProcessMessage())
	{
		imguiManager_->Begin();

		configs_->Update();

		input_->Update();

		/*////////////////////
		//	ゲーム内の処理		//
		//------------------*/

		/*////////////
		//	ImGui	//
		//----------*/



		/*----------//
		//	ImGui	//
		////////////*/

		collisionManager_->Reset();


		skydome_->Update();

		for (Floor* floor : floors_) {
			floor->Update();
		}

		enemy_->Update();
		player_->Update(aabbs_);
		weapon_->Update();

		followCamera_->Update();


		// 当たり判定
		if (enemy_->GetIsActive()) {
			collisionManager_->AddObject(enemy_.get());
		}
		if (weapon_->GetIsActive()) {
			collisionManager_->AddObject(weapon_.get());
		}
		collisionManager_->AddObject(player_.get());

		collisionManager_->CheckCollisionAll();

		/*------------------//
		//	ゲーム内の処理		//
		////////////////////*/

		imguiManager_->End();

		dxCommon_->PreDraw();

		/*////////////////
		//	描画の処理	//
		//--------------*/

		Model::PreDraw();

		/*////////////////
		//	モデル描画	//
		//--------------*/

		skydome_->Draw(vp);

		for (Floor* floor : floors_) {
			floor->Draw();
		}

		enemy_->Draw();
		player_->Draw();
		weapon_->Draw();

		/*--------------//
		//	モデル描画	//
		////////////////*/

		Model::PostDraw();





		/*--------------//
		//	描画の処理	//
		////////////////*/

		imguiManager_->Draw();

		dxCommon_->PostDraw();
	}
	aabbs_.clear();
	floors_.clear();

	imguiManager_->Finalize();

	winApp_->Finalize();
}