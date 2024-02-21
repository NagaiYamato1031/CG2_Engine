#include "Framework.h"

void Framework::Run()
{
	Initialize();
	while (true)
	{
		UpddateALL();
		if (IsEndRequest())
		{
			break;
		}
		Draw();
	}
	Finalize();
}

void Framework::Initialize()
{
	Initialize("Engine");
}

void Framework::Initialize(const std::string& title, int width, int height)
{
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize(title.c_str(), width, height);

	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize(winApp_);

	input_ = Input::GetInstance();
	input_->Initialize(winApp_);

	imguiManager_ = ImGuiManager::GetInstance();
	imguiManager_->Initialize(winApp_, dxCommon_);

	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	Sprite::StaticInitialize(winApp_, dxCommon_);

	Model::StaticInitialize(dxCommon_);

	collisionManager_.reset(new CollisionManager);

	configs_ = GlobalConfigs::GetInstance();
	configs_->LoadFiles();

	sceneManager_.reset(new SceneManager);

}

void Framework::Finalize()
{
	imguiManager_->Finalize();

	winApp_->Finalize();
}

void Framework::UpddateALL()
{
	if (winApp_->ProcessMessage())
	{
		endRequest_ = true;
		return;
	}

	imguiManager_->Begin();

	configs_->Update();

	input_->Update();
	collisionManager_->Reset();

	// ゲーム固有の処理
	Update();

	collisionManager_->CheckCollisionAll();

	imguiManager_->End();
}
