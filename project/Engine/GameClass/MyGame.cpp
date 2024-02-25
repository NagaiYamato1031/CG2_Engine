#include "MyGame.h"

#include "Application/Scene/SceneFactory.h"

MyGame::~MyGame()
{
}

void MyGame::Initialize()
{
	Framework::Initialize("LE2A_15_ナガイ_ヤマト");

	sceneFactory_.reset(new SceneFactory);
	sceneManager_->Initialize();
	sceneManager_->SetSceneFactory(sceneFactory_.get());

	sceneManager_->ChangeScene("GAMEPLAY");
}

void MyGame::Finalize()
{
	Framework::Finalize();
}

void MyGame::Update()
{
	sceneManager_->Update();
	
	ImGui::Begin("Framerate");

	ImGui::Text("%f", ImGui::GetIO().Framerate);

	ImGui::End();
}

void MyGame::Draw()
{
	dxCommon_->PreDraw();

	sceneManager_->Draw();

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
