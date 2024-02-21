#include "MyGame.h"

#include "Application/Scene/SceneFactory.h"

MyGame::~MyGame()
{
}

void MyGame::Initialize()
{
	Framework::Initialize();

	sceneFactory_.reset(new SceneFactory);
	sceneManager_->Initialize();
	sceneManager_->SetSceneFactory(sceneFactory_.get());

	sceneManager_->ChangeScene("TITLE");
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
