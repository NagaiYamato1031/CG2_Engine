#include "GameScene.h"

#include <cstdlib>
#include <time.h>

#include "Adapter/Adapter.h"
#include "Scene/SceneManager.h"


void GameScene::Initialize()
{
	BaseScene::Init();

	srand((unsigned)time(nullptr));


	view_.reset(new ViewProjection);
	view_->Initialize();
	view_->translate_ = { 0.0f,0.0f, -50.0f };

	noneList_.clear();

	map_.resize(kMAPSIZE_);
	for (size_t i = 0; i < kMAPSIZE_; i++)
	{
		map_[i].resize(kMAPSIZE_);
		for (size_t j = 0; j < kMAPSIZE_; j++)
		{
			map_[i][j] = Element::None;
			None* data = new None;
			data->Initialize();
			data->SetViewProjection(view_.get());

			data->SetPosition({ (float)j - kMAPSIZE_ / 2,(float)i - kMAPSIZE_ / 2 });
			noneList_.emplace_back(data);
		}
	}

	preMap_ = map_;

	player_.reset(new Player);
	player_->Initialize();
	player_->SetViewProjection(view_.get());

	player_->SetPosition({ 0.0f,0.0f });
	SetElement(player_.get());

	enemyList_.clear();
	for (size_t i = 0; i < rand() % 6 + 15; i++)
	{
		Enemy* data = new Enemy;
		data->Initialize();
		data->SetViewProjection(view_.get());

		int x, y;
		x = rand() % kMAPSIZE_;
		y = rand() % kMAPSIZE_;

		data->SetPosition({ (float)x - kMAPSIZE_ / 2,(float)y - kMAPSIZE_ / 2 });
		SetElement(data);

		enemyList_.emplace_back(data);
	}

	uint32_t textureHandleMove = textureManager_->Load("Move.png");

	spriteMove_.reset(Sprite::Create(textureHandleMove));

	spriteMove_->anchorPoint_ = { 0.5f,0.5f };
	spriteMove_->position_ = { 1280.0f * 0.5f,720.0f * 0.5f };

}

void GameScene::Update()
{

	/*////////////
	//	ImGui	//
	//----------*/

#ifdef _DEBUG

	ImGui::Begin("DebugConsole");

	if (ImGui::TreeNode("view"))
	{
		ImGui::DragFloat3("rotate", &view_->rotate_.x, 0.001f);
		ImGui::DragFloat3("translate", &view_->translate_.x, 0.1f);

		ImGui::TreePop();
	}

	ImGui::Separator();

	ImGui::Text("None : %d", noneList_.size());
	ImGui::Text("enemy : %d", enemyList_.size());

	Vector2 pos = player_->GetPosition();
	ImGui::Text("position : %.1f, %.1f", pos.x, pos.y);
	pos.x += kMAPSIZE_ / 2.0f;
	pos.y += kMAPSIZE_ / 2.0f;
	ImGui::Text("cposition : %.1f, %.1f", pos.x, pos.y);
	ImGui::Text("element : %d", map_[(uint32_t)pos.y][(uint32_t)pos.x]);

	ImGui::End();


#endif // _DEBUG

	/*----------//
	//	ImGui	//
	////////////*/

	/*////////////////////
	//	ゲーム内の処理		//
	//------------------*/

	if (enemyList_.size() == 0)
	{
		sceneManager_->ChangeScene("CLEAR");
	}

	if (input_->TriggerKey(DIK_R))
	{
		Initialize();
	}
	if (input_->TriggerKey(DIK_ESCAPE))
	{
		Escape();
	}

	preMap_ = map_;

	for (NoneList::iterator itr = noneList_.begin(); itr != noneList_.end(); ++itr)
	{
		(*itr)->Update();
	}

	for (EnemyList::iterator itr = enemyList_.begin(); itr != enemyList_.end();)
	{
		if (!(*itr)->GetIsActive())
		{
			itr = enemyList_.erase(itr);
			continue;
		}
		(*itr)->Update();
		++itr;
	}

	// 入力
	Vector2 movePos = player_->GetPosition();
	movePos.x += kMAPSIZE_ / 2;
	movePos.y += kMAPSIZE_ / 2;

	if (input_->TriggerKey(DIK_W))
	{
		movePos.y += 1;
		// 範囲内なら
		// 歩ける足場か確認
		if (movePos.y < kMAPSIZE_ && CheckCanMove(movePos))
		{
			player_->MoveUp();
		}
	}
	else if (input_->TriggerKey(DIK_S))
	{
		movePos.y -= 1;
		if (-1 < movePos.y && CheckCanMove(movePos))
		{
			player_->MoveDown();
		}
	}
	else if (input_->TriggerKey(DIK_A))
	{
		movePos.x -= 1;
		if (-1 < movePos.x && CheckCanMove(movePos))
		{
			player_->MoveLeft();
		}
	}
	else if (input_->TriggerKey(DIK_D))
	{
		movePos.x += 1;
		if (movePos.x < kMAPSIZE_ && CheckCanMove(movePos))
		{
			player_->MoveRight();
		}
	}

	player_->Update();

	UpdateMap();

	player_->PostUpdate();

	/*------------------//
	//	ゲーム内の処理		//
	////////////////////*/
}

void GameScene::Draw()
{
	Model::PreDraw();

	/*////////////////
	//	モデル描画	//
	//--------------*/

	for (NoneList::iterator itr = noneList_.begin(); itr != noneList_.end(); ++itr)
	{
		(*itr)->Draw();
	}

	for (EnemyList::iterator itr = enemyList_.begin(); itr != enemyList_.end(); ++itr)
	{
		(*itr)->Draw();
	}

	player_->Draw();

	/*--------------//
	//	モデル描画	//
	////////////////*/

	Model::PostDraw();

	// パーティクル描画
	//ParticleManager::GetInstance()->Draw(view_.get());


	Sprite::PreDraw();

	/*////////////////////
	//	スプライト描画		//
	//------------------*/

	spriteMove_->Draw();

	/*------------------//
	//	スプライト描画		//
	////////////////////*/

	Sprite::PostDraw();

}

void GameScene::Escape()
{
	sceneManager_->ChangeScene("TITLE");
}

void GameScene::UpdateMap()
{
	MoveElement(player_.get());
	for (EnemyList::iterator itr = enemyList_.begin(); itr != enemyList_.end(); ++itr)
	{
		Vector2 pos = (*itr)->GetPosition();
		pos.x += kMAPSIZE_ / 2.0f;
		pos.y += kMAPSIZE_ / 2.0f;
		// 齟齬が発生
		if (preMap_[(uint32_t)pos.y][(uint32_t)pos.x] == Element::Enemy &&
			map_[(uint32_t)pos.y][(uint32_t)pos.x] != Element::Enemy)
		{
			(*itr)->SetIsActive(false);
		}
	}
}

Vector2 GameScene::GetPlayerPosition()
{
	Vector2 pos = { 100.0f ,0.0f };
	for (size_t i = 0; i < kMAPSIZE_; i++)
	{
		for (size_t j = 0; j < kMAPSIZE_; j++)
		{
			if (map_[i][j] != Element::Player)
			{
				continue;
			}
			pos = { (float)j - kMAPSIZE_ / 2.0f,(float)i - kMAPSIZE_ / 2.0f };
			break;
		}
		if (pos.x != 100.0f)
		{
			break;
		}
	}
	if (pos.x == 100.0f)
	{
		pos = { 0.0f,0.0f };
	}
	return pos;
}

Vector2 GameScene::GetPlayerPositionPreview()
{
	Vector2 pos = { 100.0f ,0.0f };
	for (size_t i = 0; i < kMAPSIZE_; i++)
	{
		for (size_t j = 0; j < kMAPSIZE_; j++)
		{
			if (preMap_[i][j] != Element::Player)
			{
				continue;
			}
			pos = { (float)j - kMAPSIZE_ / 2.0f,(float)i - kMAPSIZE_ / 2.0f };
			break;
		}
		if (pos.x != 100.0f)
		{
			break;
		}
	}
	if (pos.x == 100.0f)
	{
		pos = { 0.0f,0.0f };
	}
	return pos;
}

void GameScene::SetElement(GameObject* obj)
{
	Vector2 pos = obj->GetPosition();
	pos.x += kMAPSIZE_ / 2.0f;
	pos.y += kMAPSIZE_ / 2.0f;
	map_[(uint32_t)pos.y][(uint32_t)pos.x] = obj->GetElement();
}

void GameScene::MoveElement(GameObject* obj)
{

	Vector2 prePos = obj->GetPrePosition();
	Vector2 pos = obj->GetPosition();
	if (prePos.x == pos.x && prePos.y == pos.y)
	{
		return;
	}
	prePos.x += kMAPSIZE_ / 2;
	prePos.y += kMAPSIZE_ / 2;
	map_[(uint32_t)prePos.y][(uint32_t)prePos.x] = Element::Destroy;
	// テクスチャを変えたい
	noneList_[uint32_t(prePos.y * kMAPSIZE_ + prePos.x)]->SetPosition({ 200.0f,200.0f });


	pos.x += kMAPSIZE_ / 2;
	pos.y += kMAPSIZE_ / 2;
	map_[(uint32_t)pos.y][(uint32_t)pos.x] = obj->GetElement();
}

bool GameScene::CheckCanMove(const Vector2& movePos)
{
	if (map_[(uint32_t)movePos.y][(uint32_t)movePos.x] == Element::Destroy)
	{
		return false;
	}
	return true;
}
