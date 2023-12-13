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

	// 任意軸回転
	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	Quaternion identity = Quaternion::IdentityQuaternion();
	Quaternion conj = Quaternion::Conjugate(q1);
	Quaternion inv = Quaternion::Inverse(q1);
	Quaternion normal = Quaternion::Normalize(q1);
	Quaternion mul1 = Quaternion::Multiply(q1, q2);
	Quaternion mul2 = Quaternion::Multiply(q2, q1);
	float norm = Quaternion::Norm(q1);

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::Text("Identity     : %.2f,%.2f,%.2f,%.2f", identity.x, identity.y, identity.z,identity.w);
	ImGui::Text("Conjugate    : %.2f,%.2f,%.2f,%.2f", conj.x, conj.y, conj.z, conj.w);
	ImGui::Text("Inverse      : %.2f,%.2f,%.2f,%.2f", inv.x, inv.y, inv.z, inv.w);
	ImGui::Text("Normalize    : %.2f,%.2f,%.2f,%.2f", normal.x, normal.y, normal.z, normal.w);
	ImGui::Text("Mul(q1,q2)   : %.2f,%.2f,%.2f,%.2f", mul1.x, mul1.y, mul1.z, mul1.w);
	ImGui::Text("Mul(q2,q1)   : %.2f,%.2f,%.2f,%.2f", mul2.x, mul2.y, mul2.z, mul2.w);
	ImGui::Text("Norm         : %.2f", norm);

	ImGui::End();

#endif // _DEBUG

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
