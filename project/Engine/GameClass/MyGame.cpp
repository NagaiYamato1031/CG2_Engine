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

	uint32_t textureHandleUV = textureManager_->Load("uvChecker.png");
	uint32_t textureHandleWHITE = textureManager_->Load("white2x2.png");

	spriteUV_.reset(Sprite::Create(textureHandleUV));
	spriteWHITE_.reset(Sprite::Create(textureHandleWHITE));
	
	spriteWHITE_->scale_ = { 10,10 };
	spriteWHITE_->position_ = { 640,360 };
	spriteWHITE_->anchorPoint_ = { 0.5f,0.5f };

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


	if (input_->PushKey(DIK_W))
	{
		spriteUV_->position_.y -= 5.0f;
	}
	if (input_->PushKey(DIK_S))
	{
		spriteUV_->position_.y += 5.0f;
	}
	if (input_->PushKey(DIK_A))
	{
		spriteUV_->position_.x -= 5.0f;
	}
	if (input_->PushKey(DIK_D))
	{
		spriteUV_->position_.x += 5.0f;
	}


	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::Text("WASD : Move Sprite");

	if (ImGui::TreeNode("Sprite"))
	{

		ImGui::DragFloat2("position", &spriteUV_->position_.x, 1.0f);
		ImGui::DragFloat2("size", &spriteUV_->scale_.x, 0.01f);
		ImGui::DragFloat("rotate", &spriteUV_->rotation_, 0.002f);
		ImGui::SliderFloat2("anchorpoint", &spriteUV_->anchorPoint_.x, 0.0f, 1.0f);

		ImGui::ColorEdit4("color", &spriteUV_->color_.x);

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

	spriteUV_->Draw();
	spriteWHITE_->Draw();	

	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();



	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
