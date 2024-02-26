#include "TitleScene.h"

#include "Adapter/Adapter.h"
#include "Scene/SceneManager.h"

void TitleScene::Initialize()
{
	BaseScene::Init();

	uint32_t textureHandleTitle = textureManager_->Load("uvChecker.png");

	spriteTItle_.reset(Sprite::Create(textureHandleTitle));

	spriteTItle_->anchorPoint_ = { 0.5f,0.5f };
	spriteTItle_->position_ = { 1280.0f * 0.5f,720.0f * 0.5f };
}

void TitleScene::Update()
{
	/*////////////////////
	//	ゲーム内の処理		//
	//------------------*/

	if (input_->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GAMEPLAY");
	}

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	if (ImGui::TreeNode("Sprite"))
	{

		ImGui::DragFloat2("position", &spriteTItle_->position_.x, 1.0f);
		ImGui::DragFloat2("size", &spriteTItle_->scale_.x, 0.01f);
		ImGui::DragFloat("rotate", &spriteTItle_->rotation_, 0.002f);
		ImGui::SliderFloat2("anchorpoint", &spriteTItle_->anchorPoint_.x, 0.0f, 1.0f);
		Vector2 size = spriteTItle_->GetTextureSize();
		ImGui::Text("TextureSize : %.2f,%.2f", size.x, size.y);
		ImGui::ColorEdit4("color", &spriteTItle_->color_.x);

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

void TitleScene::Draw()
{
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

	spriteTItle_->Draw();

	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();

}
