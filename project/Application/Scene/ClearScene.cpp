#include "ClearScene.h"

#include "Adapter/Adapter.h"
#include "Scene/SceneManager.h"

void ClearScene::Initialize()
{
	BaseScene::Init();

	uint32_t textureHandleClear = textureManager_->Load("Clear.png");
	uint32_t textureHandleSpace = textureManager_->Load("Space.png");

	spriteClear_.reset(Sprite::Create(textureHandleClear));
	spriteSpace_.reset(Sprite::Create(textureHandleSpace));

	spriteClear_->anchorPoint_ = { 0.5f,0.5f };
	spriteSpace_->anchorPoint_ = { 0.5f,0.5f };
	spriteClear_->position_ = { 1280.0f * 0.5f,720.0f * 0.5f };
	spriteSpace_->position_ = { 1280.0f * 0.5f,720.0f * 0.5f };
}

void ClearScene::Update()
{
	/*////////////////////
	//	ゲーム内の処理		//
	//------------------*/

	if (input_->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	if (ImGui::TreeNode("ClearSprite"))
	{

		ImGui::DragFloat2("position", &spriteClear_->position_.x, 1.0f);
		ImGui::DragFloat2("size", &spriteClear_->scale_.x, 0.01f);
		ImGui::DragFloat("rotate", &spriteClear_->rotation_, 0.002f);
		ImGui::SliderFloat2("anchorpoint", &spriteClear_->anchorPoint_.x, 0.0f, 1.0f);
		Vector2 size = spriteClear_->GetTextureSize();
		ImGui::Text("TextureSize : %.2f,%.2f", size.x, size.y);
		ImGui::ColorEdit4("color", &spriteClear_->color_.x);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("SpaceSprite"))
	{

		ImGui::DragFloat2("position", &spriteSpace_->position_.x, 1.0f);
		ImGui::DragFloat2("size", &spriteSpace_->scale_.x, 0.01f);
		ImGui::DragFloat("rotate", &spriteSpace_->rotation_, 0.002f);
		ImGui::SliderFloat2("anchorpoint", &spriteSpace_->anchorPoint_.x, 0.0f, 1.0f);
		Vector2 size = spriteSpace_->GetTextureSize();
		ImGui::Text("TextureSize : %.2f,%.2f", size.x, size.y);
		ImGui::ColorEdit4("color", &spriteSpace_->color_.x);

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

void ClearScene::Draw()
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

	spriteClear_->Draw();
	spriteSpace_->Draw();

	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();

}
