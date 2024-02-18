#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	models_.push_back(model);

	transformBase_.Initialize();
	transformBase_.translate_ = { 0.0f, 0.0f, 0.0f };
	transformBase_.scale_ = { 500.0f, 500.0f, 500.0f };
}

void Skydome::Update() {}

void Skydome::Draw(ViewProjection* viewProjeciton) {
	models_[0]->Draw(&transformBase_, viewProjeciton);
}

void Skydome::DebugGUI()
{
}
