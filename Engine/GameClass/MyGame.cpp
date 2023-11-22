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

	vp = new ViewProjection;
	vp->Initialize();

	particle_.reset(Particle::CreateOBJ("resources", "uvChecker.png", 10));

	for (size_t i = 0; i < kNumIndex_; i++)
	{
		wt[i].Initialize();
		wt[i].translate_ = { i * 0.1f,i * 0.1f,i * 0.1f };
	}

	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


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

	ImGui::Begin("DebugConsole");

	if (ImGui::TreeNode("Camera")) {
		ImGui::DragFloat3("rotate", &vp->rotate_.x, 0.002f);
		ImGui::DragFloat3("translate", &vp->translate_.x, 0.01f);

		ImGui::TreePop();
	}


	ImGui::End();

	/*----------//
	//	ImGui	//
	////////////*/



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


	/*--------------//
	//	モデル描画	//
	////////////////*/

	Model::PostDraw();

	Particle::PreDraw();

	/*////////////////////
	//	パーティクル描画	//
	//------------------*/

	particle_->Draw(wt, vp);

	/*------------------//
	//	パーティクル描画	//
	////////////////////*/

	Particle::PostDraw();

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
