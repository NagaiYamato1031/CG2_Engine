#include "Floor.h"

void Floor::Initialize(Model* model, bool isMove)
{
	models_.push_back(model);
	transformBase_.Initialize();
	transformBase_.scale_ = { 1.0f,1.0f,1.0f };
	start_ = { 0.0f,0.0f,0.0f };
	end_ = { 0.0f,0.0f,0.0f };
	isMove_ = isMove;

	aabb.min_ = { -10.0f,-1.0f,-10.0f };
	aabb.max_ = { 10.0f,1.0f,10.0f };
	aabb.transform_.SetParent(&transformBase_);
}

void Floor::Update()
{
	DebugGUI();

	Vector3 move{ 0.0f,0.0f,0.0f };
	if (isMove_) {
		moveT_ += movingT_;
		if (moveT_ <= 0.0f || 1 <= moveT_) {
			movingT_ = -movingT_;
		}
		if (moveT_ < 0.5f) {
			float t = 4 * moveT_ * moveT_ * moveT_;
			move = (end_ - start_) * t;
		}
		else if (0.5f <= moveT_) {
			float t = 1 - std::powf(-2.0f * moveT_ + 2.0f, 3.0f) / 2.0f;
			move = (end_ - start_) * t;
		}
	}
	transformBase_.translate_ = start_ + move;

	// AABB を連結
	// 当たり判定を取るときに連結する
}

void Floor::Draw()
{
	models_[0]->Draw(&transformBase_, viewProjection_);
}

void Floor::DebugGUI()
{
#ifdef _DEBUG

#endif // _DEBUG

}

void Floor::SetTexture(uint32_t texture)
{
	models_[0]->SetTexture(texture);
}
