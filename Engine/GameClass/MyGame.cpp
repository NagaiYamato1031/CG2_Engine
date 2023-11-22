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
	Vector3 axis = Vector3::Normalize({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;
	Matrix4x4 rotateMatrix = Matrix4x4::MakeRotateAxisMatrix(axis,angle);


	/*////////////
	//	ImGui	//
	//----------*/

	ImGui::Begin("DebugConsole");

	ImGui::Text("rotateMatrix");
	ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3]);
	ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3]);
	ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3]);
	ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);

	ImGui::End();

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
