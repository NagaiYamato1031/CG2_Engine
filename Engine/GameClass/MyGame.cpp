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

	uint32_t textureHandle = textureManager_->Load("uvChecker.png");
	vp = new ViewProjection;
	vp->Initialize();

	sprite_.reset(Sprite::Create(textureHandle));
	//sprite_->Initialize();
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

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::End();


#endif // _DEBUG

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
	
	Sprite::PreDraw();

	/*////////////////////
	//	スプライト描画		//
	//------------------*/

	sprite_->Draw();

	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();




	Particle::PreDraw();

	/*////////////////////
	//	パーティクル描画	//
	//------------------*/

	///particle_->Draw(wt, vp);

	/*------------------//
	//	パーティクル描画	//
	////////////////////*/

	Particle::PostDraw();

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
