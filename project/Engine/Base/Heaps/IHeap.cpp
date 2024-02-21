#include "IHeap.h"

#include "Base/DirectXCommon.h"

D3D12_CPU_DESCRIPTOR_HANDLE IHeap::GetCPUHandleStart() const
{
	return heap_->GetCPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE IHeap::GetGPUHandleStart() const
{
	return heap_->GetGPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE IHeap::GetCPUHandle() const
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = heap_->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += static_cast<UINT64>(kDescriptorSize_) * static_cast<UINT64>(useCount_);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE IHeap::GetGPUHandle() const
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = heap_->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += static_cast<UINT64>(kDescriptorSize_) * static_cast<UINT64>(useCount_);
	return handleGPU;
}

D3D12_CPU_DESCRIPTOR_HANDLE IHeap::GetDescriptorHandleIncrementSize(int offsetInDescriptors)const
{
	// ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE handle;
	if (offsetInDescriptors <= 0)
	{
		handle = this->GetCPUHandleStart();
	}
	else
	{
		handle.ptr = this->GetCPUHandleStart().ptr + (kDescriptorSize_ * offsetInDescriptors);
	}

	return handle;
}


ID3D12DescriptorHeap* IHeap::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescrioptors, bool shaderVisible)
{
	HRESULT hr = S_FALSE;
	// ディスクリプタヒープの生成
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;
	descriptorHeapDesc.NumDescriptors = numDescrioptors;
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ID3D12DescriptorHeap* heap = nullptr;
	hr = DirectXCommon::GetInstance()->GetDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&heap));
	// ディスクリプタヒープが作れなかったので起動できない
	assert(SUCCEEDED(hr));
	return heap;
}
