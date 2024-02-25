#include "GameScene.h"

#include "Adapter/Adapter.h"
#include "Scene/SceneManager.h"

void GameScene::Initialize()
{
	BaseScene::Init();

	view_.reset(new ViewProjection);
	view_->Initialize();
}

void GameScene::Update()
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

void GameScene::Draw()
{
	Model::PreDraw();

	/*////////////////
	//	モデル描画	//
	//--------------*/


	/*--------------//
	//	モデル描画	//
	////////////////*/

	Model::PostDraw();

	// パーティクル描画
	//ParticleManager::GetInstance()->Draw(view_.get());


	Sprite::PreDraw();

	/*////////////////////
	//	スプライト描画		//
	//------------------*/


	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();

}
