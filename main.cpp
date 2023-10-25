#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"
#include "Engine/Model/ModelManager.h"
#include "Engine/Resource/Texture/TextureManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	ModelManager* modelManager_ = nullptr;

	winApp_ = WinApp::GetInstance();
	winApp_->Initialize("Engine", 1280, 720);

	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize(winApp_);

	input_ = Input::GetInstance();
	input_->Initialize(winApp_);

	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	modelManager_ = ModelManager::GetInstance();
	modelManager_->Initialize(dxCommon_);

	Model::StaticInitialize();

	WorldTransform transform;
	transform.Initialize();

	Model* model_ = new Model(&transform);
	model_->Initialize("resources", "plane.obj");

	while (!winApp_->ProcessMessage())
	{
		input_->Update();

		// ここにゲーム内の処理を書く




		//////////

		dxCommon_->PreDraw();

		// ここから描画を書く

		Model::PreDraw();

		model_->Draw();

		Model::PostDraw();


		//////////

		dxCommon_->PostDraw();
	}



	winApp_->Finalize();
}