#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>

#include <wrl.h>
#include <chrono>
#include <vector>
#include "./WinApp.h"

class DirectXCommon
{
public: // メンバ関数
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	static DirectXCommon* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画語処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// レンダーターゲットのクリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 深度バッファのクリア
	/// </summary>
	void ClearDepthBuffer();

	// アクセサ
	ID3D12Device* GetDevice() const { return device_.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList_.Get(); }
	ID3D12CommandQueue* GetCommandQueue() const { return commandQueue_.Get(); }
	ID3D12CommandAllocator* GetCommandAllocator() const { return commandAllocateor_.Get(); }
	size_t GetBackBufferCount() const { return backBuffers_.size(); }
	ID3D12Fence* GetFence() const { return fence_.Get(); }
	
	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);

	/// <summary>
	/// ディスクリプタヒープの作成
	/// </summary>
	/// <param name="heapType">ヒープのタイプ</param>
	/// <param name="numDescrioptors">作るディスクリプタの数</param>
	/// <param name="shaderVisible">シェーダーで触れるか</param>
	/// <returns></returns>
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescrioptors, bool shaderVisible);

private: // メンバ変数
	// ウィンドウズアプリケーション管理
	WinApp* winApp_ = nullptr;

	// Direct3D関連
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocateor_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal_ = 0;
	int32_t backBufferWidth_ = 0;
	int32_t backBufferHeight_ = 0;

private:

	// 記録時間(FPS 固定)
	std::chrono::steady_clock::time_point reference_;

private: // 非公開のメンバ関数
	DirectXCommon() = default;
	~DirectXCommon() = default;
	DirectXCommon(const DirectXCommon&) = delete;
	const DirectXCommon& operator=(const DirectXCommon&) = delete;

	/// <summary>
	/// DXGIデバイス初期化
	/// </summary>
	void InitializeDXGIDevice();

	/// <summary>
	/// コマンド関連初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// レンダーターゲット生成
	/// </summary>
	void CreateFinalRenderTargets();

	/// <summary>
	/// 深度バッファ初期化
	/// </summary>
	void CreateDepthBuffer();

	/// <summary>
	/// フェンス生成
	/// </summary>
	void CreateFence();

	/// <summary>
	///　デスクリプタヒープのデスクリプタハンドル増分サイズを返す関数
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandleIncrementSize(const D3D12_CPU_DESCRIPTOR_HANDLE&, int, UINT);

	/// <summary>
	/// リソースバリアの実態を作る関数
	/// </summary>
	D3D12_RESOURCE_BARRIER MakeResourceBarrier(ID3D12Resource*, D3D12_RESOURCE_STATES, D3D12_RESOURCE_STATES);

	/// <summary>
	/// FPS 固定初期化
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS 固定更新
	/// </summary>
	void UpdateFixFPS();
};

