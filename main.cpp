#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/ImGui/ImGuiManager.h"
#include "Engine/Resource/Texture/TextureManager.h"
#include "Engine/Model/Model.h"

#include "Engine/Object/ViewProjection.h"

#include "Engine/Object/3D/3dObjectList.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager* imguiManager_ = nullptr;
	TextureManager* textureManager_ = nullptr;



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

	/*////////////////////
	//	ゲームで使う変数	//
	//------------------*/

	ViewProjection* vp = new ViewProjection();
	vp->Initialize();

	std::unique_ptr<Model> modelFence_;
	modelFence_.reset(Model::CreateOBJ("resources/fence", "fence.obj"));

	WorldTransform wt;
	wt.Initialize();
	wt.rotate_.y = 3.14f;


	std::unique_ptr<Model> modelPlane_;
	modelPlane_.reset(Model::CreateOBJ("resources/plane", "plane.obj"));

	WorldTransform wt2;
	wt2.Initialize();


	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


	while (!winApp_->ProcessMessage())
	{
		imguiManager_->Begin();

		//input_->Update();

		/*////////////////////
		//	ゲーム内の処理		//
		//------------------*/

		/*////////////
		//	ImGui	//
		//----------*/

		ImGui::Begin("DebugCamera");

		ImGui::DragFloat3("rotate1", &vp->rotate_.x, 0.01f);
		ImGui::DragFloat3("translate1", &vp->translate_.x, 0.05f);

		ImGui::Separator();

		ImGui::DragFloat3("rotate2", &wt.rotate_.x, 0.01f);
		ImGui::DragFloat3("translate2", &wt.translate_.x, 0.05f);

		ImGui::Separator();

		ImGui::DragFloat3("rotate3", &wt2.rotate_.x, 0.01f);
		ImGui::DragFloat3("translate3", &wt2.translate_.x, 0.05f);

		ImGui::End();

		/*----------//
		//	ImGui	//
		////////////*/



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

		modelFence_->Draw(&wt, vp);
		modelPlane_->Draw(&wt2, vp);

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

	imguiManager_->Finalize();

	winApp_->Finalize();
}