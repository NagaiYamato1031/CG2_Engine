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
	Quaternion rotation = Quaternion::MakeRotateAxisAngleQuaternion(Vector3::Normalize({ 1.0f,0.4f,-0.2f }), 0.45f);
	Vector3 pointY{ 2.1f, -0.9f,1.3f };
	Matrix4x4 rotateMatrix = Quaternion::MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = Quaternion::RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Vector3::Transform(pointY, rotateMatrix);


	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	ImGui::Text("rotation        : %.2f,%.2f,%.2f,%.2f", rotation.x, rotation.y, rotation.z, rotation.w);
	
	ImGui::Text("rotateMatrix");
	ImGui::Text("[%.3f],%.3f,%.3f,%.3f", rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3]);
	ImGui::Text("%.3f,%.3f,%.3f,%.3f", rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3]);
	ImGui::Text("%.3f,%.3f,%.3f,%.3f", rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3]);
	ImGui::Text("%.3f,%.3f,%.3f,%.3f", rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);

	ImGui::Text("rotateQuaternion: %.2f,%.2f,%.2f", rotateByQuaternion.x,rotateByQuaternion.y,rotateByQuaternion.z);
	ImGui::Text("rotateMatrix    : %.2f,%.2f,%.2f", rotateByMatrix.x, rotateByMatrix.y, rotateByMatrix.z);

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
