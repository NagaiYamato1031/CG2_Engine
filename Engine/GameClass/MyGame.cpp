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
	Vector3 from0 = Vector3::Normalize({ 1.0f,0.7f,0.5f });
	Vector3 to0 = -from0;
	Vector3 from1 = Vector3::Normalize({ -0.6f,0.9f,0.2f });
	Vector3 to1 = Vector3::Normalize({ 0.4f,0.7f,-0.5f });

	Matrix4x4 rotateMatrix0 = Matrix4x4::DirectionToDirection(Vector3::Normalize({ 1.0f,0.0f,0.0f }), Vector3::Normalize({ -1.0f,0.0f,0.0f }));
	Matrix4x4 rotateMatrix1 = Matrix4x4::DirectionToDirection(from0, to0);
	Matrix4x4 rotateMatrix2 = Matrix4x4::DirectionToDirection(from1, to1);

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	if (ImGui::TreeNode("rotateMatrix0"))
	{
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix0.m[0][0], rotateMatrix0.m[0][1], rotateMatrix0.m[0][2], rotateMatrix0.m[0][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix0.m[1][0], rotateMatrix0.m[1][1], rotateMatrix0.m[1][2], rotateMatrix0.m[1][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix0.m[2][0], rotateMatrix0.m[2][1], rotateMatrix0.m[2][2], rotateMatrix0.m[2][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix0.m[3][0], rotateMatrix0.m[3][1], rotateMatrix0.m[3][2], rotateMatrix0.m[3][3]);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("rotateMatrix1"))
	{
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix1.m[0][0], rotateMatrix1.m[0][1], rotateMatrix1.m[0][2], rotateMatrix1.m[0][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix1.m[1][0], rotateMatrix1.m[1][1], rotateMatrix1.m[1][2], rotateMatrix1.m[1][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix1.m[2][0], rotateMatrix1.m[2][1], rotateMatrix1.m[2][2], rotateMatrix1.m[2][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix1.m[3][0], rotateMatrix1.m[3][1], rotateMatrix1.m[3][2], rotateMatrix1.m[3][3]);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("rotateMatrix2"))
	{
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix2.m[0][0], rotateMatrix2.m[0][1], rotateMatrix2.m[0][2], rotateMatrix2.m[0][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix2.m[1][0], rotateMatrix2.m[1][1], rotateMatrix2.m[1][2], rotateMatrix2.m[1][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix2.m[2][0], rotateMatrix2.m[2][1], rotateMatrix2.m[2][2], rotateMatrix2.m[2][3]);
		ImGui::Text("%.3f\t%.3f\t%.3f\t%.3f", rotateMatrix2.m[3][0], rotateMatrix2.m[3][1], rotateMatrix2.m[3][2], rotateMatrix2.m[3][3]);
		ImGui::TreePop();
	}


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
