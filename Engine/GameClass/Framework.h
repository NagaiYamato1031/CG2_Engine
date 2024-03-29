#pragma once

#include "../Adapter/Adapter.h"

class Framework
{
protected:

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	ImGuiManager* imguiManager_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	std::unique_ptr<CollisionManager> collisionManager_;

	GlobalConfigs* configs_ = nullptr;

	bool endRequest_ = false;

public:

	virtual ~Framework() = default;

	void Run();

protected:

	virtual void Initialize();

	virtual void Finalize();

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual bool IsEndRequest() { return endRequest_; }

private:

	void UpddateALL();

};