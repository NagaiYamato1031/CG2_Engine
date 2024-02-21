#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <imgui.h>

#include "../Base/WinApp.h"
#include "../Base/DirectXCommon.h"

class ImGuiManager final
{
public:

	static ImGuiManager* GetInstance();

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Begin();
	void End();

	void Draw();

	void Finalize();

private:

	ImGuiManager() = default;
	~ImGuiManager() = default;
	ImGuiManager(const ImGuiManager&) = delete;
	const ImGuiManager& operator=(const ImGuiManager&) = delete;

private:

	DirectXCommon* dxCommon_ = nullptr;
};