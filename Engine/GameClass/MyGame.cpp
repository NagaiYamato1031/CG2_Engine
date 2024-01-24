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

	sprite_.reset(Sprite::Create(textureHandle));
	sprite_->Initialize();


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

	if (ImGui::TreeNode("Sprite"))
	{

		ImGui::DragFloat2("position", &sprite_->position_.x, 0.01f);
		ImGui::DragFloat2("size", &sprite_->scale_.x, 0.01f);
		ImGui::SliderFloat2("anchorpoint", &sprite_->anchorPoint_.x, 0.0f, 1.0f);

		ImGui::ColorPicker4("color", &sprite_->color_.x);

		ImGui::TreePop();
	}
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



	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
