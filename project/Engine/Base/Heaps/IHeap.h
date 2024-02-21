#pragma once

#include <cstdint>
#include <wrl.h>
#include <d3d12.h>

class IHeap
{
public:

	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;

	// ヒープ全体の大きさ
	uint32_t heapSize_;

	// ディスクリプタ一つの大きさ
	uint32_t kDescriptorSize_ = 0u;

	// インデックス
	uint32_t useCount_ = 0u;

public:
	~IHeap() = default;

	ID3D12DescriptorHeap* GetHeap() { return heap_.Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandleStart() const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleStart() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle() const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const;

	D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandleIncrementSize(int offsetInDescriptors) const;

	uint32_t GetDescriptorSize() const { return kDescriptorSize_; }
	uint32_t GetCount() const { return useCount_; }
	void Increment() { useCount_++; }

protected:

	/// <summary>
	/// ディスクリプタヒープの作成
	/// </summary>
	/// <param name="heapType">ヒープのタイプ</param>
	/// <param name="numDescrioptors">作るディスクリプタの数</param>
	/// <param name="shaderVisible">シェーダーで触れるか</param>
	/// <return></return>
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescrioptors, bool shaderVisible);

};