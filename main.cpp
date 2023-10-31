#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/ImGui/ImGuiManager.h"
#include "Engine/Resource/Texture/TextureManager.h"
#include "Engine/Model/Model.h"

#include "Engine/Object/ViewProjection.h"

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

	Model* md1 = Model::CreateOBJ("resources", "axis.obj");
	Model* md2 = Model::CreateOBJ("resources", "plane.obj");

	ViewProjection vp;
	vp.Initialize();

	WorldTransform axisWT;
	axisWT.Initialize();

	WorldTransform planeWT;
	planeWT.Initialize();

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

		ImGui::Begin("Axis");

		ImGui::DragFloat3("scale", &axisWT.scale_.x, 0.01f);
		ImGui::DragFloat3("rotate", &axisWT.rotate_.x, 0.01f);
		ImGui::DragFloat3("translate", &axisWT.translate_.x, 0.01f);

		ImGui::End();

		

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

		md1->Draw(&axisWT,&vp);

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

	delete md1;

	imguiManager_->Finalize();

	winApp_->Finalize();
}