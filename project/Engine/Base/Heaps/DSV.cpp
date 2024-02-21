#include "DSV.h"

#include "Base/DirectXCommon.h"

void DSV::Initialize()
{
	heapSize_ = 1;
	// ディスクリプタ一つのサイズを取得
	kDescriptorSize_ = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	heap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, heapSize_, false);
}
