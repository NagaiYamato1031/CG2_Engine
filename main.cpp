#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/ImGui/ImGuiManager.h"
#include "Engine/Resource/Texture/TextureManager.h"
#include "Engine/Model/Model.h"

#include "Engine/Object/ViewProjection.h"

#include "Engine/Object/3D/Player/Player.h"

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

	ViewProjection vp;
	vp.Initialize();

	std::unique_ptr<Model> modelPlayerBody_;
	std::unique_ptr<Model> modelPlayerHead_;
	std::unique_ptr<Model> modelPlayerL_arm_;
	std::unique_ptr<Model> modelPlayerR_arm_;

	modelPlayerBody_.reset(Model::CreateOBJ("resources", "player_Body.obj"));
	modelPlayerHead_.reset(Model::CreateOBJ("resources", "player_Head.obj"));
	modelPlayerL_arm_.reset(Model::CreateOBJ("resources", "player_L_arm.obj"));
	modelPlayerR_arm_.reset(Model::CreateOBJ("resources", "player_R_arm.obj"));

	std::vector<Model*> playerModels = {
		modelPlayerBody_.get(),modelPlayerHead_.get(),
		modelPlayerL_arm_.get(),modelPlayerR_arm_.get()
	};

	std::unique_ptr<Player> player_;
	player_.reset(new Player);
	player_->Initialize(playerModels);

	player_->SetViewProjection(&vp);

	Model* md2 = Model::CreateOBJ("resources", "plane.obj");

	WorldTransform planeWT;
	planeWT.Initialize();

	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


	while (!winApp_->ProcessMessage())
	{
		imguiManager_->Begin();

		input_->Update();

		/*////////////////////
		//	ゲーム内の処理		//
		//------------------*/

		/*////////////
		//	ImGui	//
		//----------*/


		ImGui::Begin("Plane");

		ImGui::DragFloat3("scale", &planeWT.scale_.x, 0.01f);
		ImGui::DragFloat3("rotate", &planeWT.rotate_.x, 0.01f);
		ImGui::DragFloat3("translate", &planeWT.translate_.x, 0.01f);

		ImGui::End();


		ImGui::Begin("ViewProjection");

		ImGui::DragFloat3("rotate", &vp.rotate_.x, 0.01f);
		ImGui::DragFloat3("translate", &vp.translate_.x, 0.01f);

		ImGui::End();

		/*----------//
		//	ImGui	//
		////////////*/


		player_->Update();








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

		player_->Draw();

		md2->Draw(&planeWT, &vp);

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