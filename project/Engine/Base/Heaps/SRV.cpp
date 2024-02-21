#include "SRV.h"

#include "Base/DirectXCommon.h"

void SRV::Initialize()
{
	heapSize_ = 128;
	// ディスクリプタ一つのサイズを取得
	kDescriptorSize_ = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	heap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, heapSize_, true);

	// ImGui が一番目を使っているためインクリメント
	useCount_++;
}
