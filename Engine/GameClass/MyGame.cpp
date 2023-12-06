#include "MyGame.h"

MyGame::~MyGame()
{
}

void MyGame::Initialize()
{
	Framework::Initialize();

	/*////////////////////
	//	ゲームで使う変数	//
	//------------------*/

	camera_.reset(new Camera);
	camera_->Initialize();

	vp = camera_->GetViewProjection();

	modelSkydome_.reset(Model::CreateOBJ("resources/skydome", "skydome.obj"));

	skydome_.reset(new Skydome());
	skydome_->Initialize(modelSkydome_.get());


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

	weapon_.reset(new Weapon);

	player_.reset(new Player);
	player_->Initialize(playerModels);

	player_->SetViewProjection(vp);
	camera_->SetTarget(player_->GetWorldTransform());

	player_->SetWeapon(weapon_.get());
	weapon_->SetViewProjection(vp);

	player_->SetMyGame(this);

	for (size_t i = 0; i < 5; i++)
	{
		enemys_.emplace_back(new Enemy);
	}
	for (size_t i = 0; i < 5; i++)
	{
		modelEnemyBodys_.emplace_back(Model::CreateOBJ("resources/enemy", "enemy_Body.obj"));
		modelEnemyHeads_.emplace_back(Model::CreateOBJ("resources/enemy", "enemy_Head.obj"));
	}
	for (int i = 0; i < 5; i++)
	{
		std::vector<Model*> enemyModels = {
			modelEnemyBodys_[i].get(),modelEnemyHeads_[i].get(),
		};

		enemys_[i]->Initialize(enemyModels);
		enemys_[i]->SetViewProjection(vp);
		enemys_[i]->SetPopPosition({ 4.0f + (3 - i) * 8.0f,0.0f, 4.0f + i * 6.0f });
		enemys_[i]->Reset();
	}

	modelFloor0.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	floor0.reset(new Floor);
	floor0->Initialize(modelFloor0.get(), false);
	floor0->start_ = { 0.0f,0.0f,0.0f };
	floor0->end_ = { 0.0f,0.0f,0.0f };
	floor0->SetScale({ 25.0f,1.0f,25.0f });
	floor0->isMove_ = false;

	modelFloor1.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	floor1.reset(new Floor);
	floor1->Initialize(modelFloor1.get(), false);
	floor1->start_ = { 18.0f,4.0f,20.0f };
	floor1->end_ = { 4.0f,7.0f,57.0f };
	floor1->isMove_ = true;

	modelFloor2.reset(Model::CreateOBJ("resources/plane", "plane.obj"));
	floor2.reset(new Floor);
	floor2->Initialize(modelFloor2.get(), false);
	floor2->start_ = { -20.0f,10.0f,60.0f };
	floor2->end_ = { 0.0f,0.0f,0.0f };
	floor2->isMove_ = false;



	// 床をまとめる
	floors_.push_back(floor0.get());
	floors_.push_back(floor1.get());
	floors_.push_back(floor2.get());

	//aabbs_.push_back(enemy_->GetAABB());

	for (Floor*& floor : floors_)
	{
		floor->SetViewProjection(vp);
		aabbs_.push_back(&floor->aabb);
	}

	uint32_t textureWhite_ = TextureManager::Load("white2x2.png");
	floor1->SetTexture(textureWhite_);
	floor2->SetTexture(textureWhite_);

	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


}

void MyGame::Reset()
{
	for (size_t i = 0; i < enemys_.size(); i++)
	{
		enemys_[i]->Reset();
	}
}

void MyGame::Finalize()
{
	Framework::Finalize();
}

void MyGame::Update()
{
	/*////////////////////
	//	ゲーム内の処理		//
	//------------------*/

	/*////////////
	//	ImGui	//
	//----------*/



	/*----------//
	//	ImGui	//
	////////////*/


	skydome_->Update();

	for (Floor* floor : floors_)
	{
		floor->Update();
	}

	for (size_t i = 0; i < enemys_.size(); i++)
	{
		enemys_[i]->Update();
	}

	player_->Update(aabbs_);
	weapon_->Update();

	camera_->Update();

	for (size_t i = 0; i < enemys_.size(); i++)
	{
		// 当たり判定
		if (enemys_[i]->GetIsActive())
		{
			collisionManager_->AddObject(enemys_[i].get());
		}
	}
	if (weapon_->GetIsActive())
	{
		collisionManager_->AddObject(weapon_.get());
	}
	collisionManager_->AddObject(player_.get());

	/*------------------//
	//	ゲーム内の処理		//
	////////////////////*/
}

void MyGame::Draw()
{
	dxCommon_->PreDraw();

	Model::PreDraw();

	/*////////////////
	//	モデル描画	//
	//--------------*/

	skydome_->Draw(vp);

	for (Floor* floor : floors_)
	{
		floor->Draw();
	}

	for (size_t i = 0; i < enemys_.size(); i++)
	{
		enemys_[i]->Draw();
	}
	player_->Draw();
	weapon_->Draw();

	/*--------------//
	//	モデル描画	//
	////////////////*/



	Model::PostDraw();

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
