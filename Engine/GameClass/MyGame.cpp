#include "MyGame.h"

MyGame::~MyGame()
{
}

void MyGame::Initialize()
{
	Framework::Initialize();

	/*////////////////////
	//	ゲームで使う変数	//
	//------------------*/

	vp = new ViewProjection;
	vp->Initialize();

	particle_.reset(Particle::CreateOBJ("resources", "uvChecker.png", 10));

	for (size_t i = 0; i < kNumIndex_; i++)
	{
		wt[i].Initialize();
		wt[i].translate_ = { i * 0.1f,i * 0.1f,i * 0.1f };
	}

	/*------------------//
	//	ゲームで使う変数	//
	////////////////////*/


}

void MyGame::Finalize()
{
	Framework::Finalize();
}

void MyGame::Update()
{
	/*////////////////////
	//	ゲーム内の処理		//
	//------------------*/

	// 任意軸回転
	Quaternion rotation0 = Quaternion::MakeRotateAxisAngleQuaternion(Vector3::Normalize({ 0.71f,0.71f,0.0f }), 0.3f);
	Quaternion rotation1 = -rotation0;

	Quaternion interpolate0 = Quaternion::Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Quaternion::Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Quaternion::Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Quaternion::Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Quaternion::Slerp(rotation0, rotation1, 1.0f);

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::Text("rotation0		: %.2f,%.2f,%.2f,%.2f", rotation0.x, rotation0.y, rotation0.z, rotation0.w);
	ImGui::Text("rotation1		: %.2f,%.2f,%.2f,%.2f", rotation1.x, rotation1.y, rotation1.z, rotation1.w);
	ImGui::Text("");
	ImGui::Text("interpolate0	: %.2f,%.2f,%.2f,%.2f", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
	ImGui::Text("interpolate1	: %.2f,%.2f,%.2f,%.2f", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
	ImGui::Text("interpolate2	: %.2f,%.2f,%.2f,%.2f", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
	ImGui::Text("interpolate3	: %.2f,%.2f,%.2f,%.2f", interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);
	ImGui::Text("interpolate4	: %.2f,%.2f,%.2f,%.2f", interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);

	ImGui::End();

#endif // _DEBUG

	/*----------//
	//	ImGui	//
	////////////*/



	/*------------------//
	//	ゲーム内の処理		//
	////////////////////*/
}

void MyGame::Draw()
{
	dxCommon_->PreDraw();

	Model::PreDraw();

	/*////////////////
	//	モデル描画	//
	//--------------*/


	/*--------------//
	//	モデル描画	//
	////////////////*/

	Model::PostDraw();

	Particle::PreDraw();

	/*////////////////////
	//	パーティクル描画	//
	//------------------*/

	particle_->Draw(wt, vp);

	/*------------------//
	//	パーティクル描画	//
	////////////////////*/

	Particle::PostDraw();

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
