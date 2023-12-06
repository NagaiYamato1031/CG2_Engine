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
	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	Quaternion identity = Quaternion::IdentityQuaternion();
	Quaternion conj = Quaternion::Conjugate(q1);
	Quaternion inv = Quaternion::Inverse(q1);
	Quaternion normal = Quaternion::Normalize(q1);
	Quaternion mul1 = Quaternion::Multiply(q1, q2);
	Quaternion mul2 = Quaternion::Multiply(q2, q1);
	float norm = Quaternion::Norm(q1);

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::Text("Identity     : %.2f,%.2f,%.2f,%.2f", identity.x, identity.y, identity.z,identity.w);
	ImGui::Text("Conjugate    : %.2f,%.2f,%.2f,%.2f", conj.x, conj.y, conj.z, conj.w);
	ImGui::Text("Inverse      : %.2f,%.2f,%.2f,%.2f", inv.x, inv.y, inv.z, inv.w);
	ImGui::Text("Normalize    : %.2f,%.2f,%.2f,%.2f", normal.x, normal.y, normal.z, normal.w);
	ImGui::Text("Mul(q1,q2)   : %.2f,%.2f,%.2f,%.2f", mul1.x, mul1.y, mul1.z, mul1.w);
	ImGui::Text("Mul(q2,q1)   : %.2f,%.2f,%.2f,%.2f", mul2.x, mul2.y, mul2.z, mul2.w);
	ImGui::Text("Norm         : %.2f", norm);

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

	imguiManager_->Draw();

	dxCommon_->PostDraw();
}
