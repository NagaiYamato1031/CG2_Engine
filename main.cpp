#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/ImGui/ImGuiManager.h"
#include "Engine/Resource/Texture/TextureManager.h"
#include "Engine/Model/Model.h"

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

	Model* model = Model::CreateOBJ("resources","axis.obj");


	while (!winApp_->ProcessMessage())
	{
		imguiManager_->Begin();

		input_->Update();

		// ここにゲーム内の処理を書く



		//////////
		imguiManager_->End();

		dxCommon_->PreDraw();

		// ここから描画を書く


		//////////
		imguiManager_->Draw();

		dxCommon_->PostDraw();
	}

	delete model;

	imguiManager_->Finalize();

	winApp_->Finalize();
}