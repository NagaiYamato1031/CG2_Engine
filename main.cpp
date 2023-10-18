#include "Engine/Base/WinApp.h"
#include "Engine/Base/DirectXCommon.h"
#include "Engine/Input/Input.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	winApp_ = WinApp::GetInstance();
	winApp_->Initialize("Engine", 1280, 720);

	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize(winApp_);
	
	input_ = Input::GetInstance();
	input_->Initialize(winApp_);


	//CanvasTool* sCanvasTool = CanvasTool::GetInstance();
	//sCanvasTool->Initialize(sDXCommon);

	while (!winApp_->ProcessMessage())
	{
		input_->Update();

		// ここにゲーム内の処理を書く




		//////////

		dxCommon_->PreDraw();

		// ここから描画を書く
		

		//////////

		dxCommon_->PostDraw();
	}

	winApp_->Finalize();
}