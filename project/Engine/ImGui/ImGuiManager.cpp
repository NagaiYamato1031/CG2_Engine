#include "ImGuiManager.h"
#include "../Utility/MyUtility.h"

#include <cassert>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager instance;
	return &instance;
}

void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{
	assert(winApp);
	assert(dxCommon);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(winApp->GetHWND());

	dxCommon_ = dxCommon;

	SRV* srvHeap = dxCommon_->GetSRV();

	ImGui_ImplDX12_Init(
		dxCommon_->GetDevice(),
		static_cast<int>(dxCommon_->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		srvHeap->GetHeap(),
		srvHeap->GetCPUHandleStart(),
		srvHeap->GetGPUHandleStart()
	);

	ImGuiIO& io = ImGui::GetIO();
	// 標準フォント
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Begin()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon_->GetCommandList();

	ID3D12DescriptorHeap* ppHeaps[] = { dxCommon_->GetSRV()->GetHeap() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);

}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
